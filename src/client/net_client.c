#include <errno.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <shared/logger.h>
#include <shared/system.h>

#include "net_client.h"

void netclient_init(NetClient *client) {
	client->socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(client->socket < 0) {
		log_error("client", "failed to create socket");
		return;
	}

	client->addr.sin_family = AF_INET;
	client->addr.sin_port = 0;
	char ip[4] = {127, 0, 0, 1};
	memcpy(&client->addr.sin_addr.s_addr, ip, 4);

	errno = 0;
	int err = bind(client->socket, (struct sockaddr *)&client->addr, sizeof(client->addr));
	if(err) {
		close(client->socket);
		log_error("client", "failed to bind: %s", strerror(errno));
		return;
	}

	int broadcast = 1;
	setsockopt(client->socket, SOL_SOCKET, SO_BROADCAST, (const char *)&broadcast, sizeof(broadcast));

	int recvsize = 65536;
	setsockopt(client->socket, SOL_SOCKET, SO_RCVBUF, (char *)&recvsize, sizeof(recvsize));

	unsigned long mode = 1;
	ioctl(client->socket, FIONBIO, &mode);

	log_info("client", "got socket %d", client->socket);
}

void netclient_connect(NetClient *client, const char *addr) {
	// TODO: actually parse the address

	client->server_addr.sin_family = AF_INET;
	client->server_addr.sin_port = htons(8303);
	unsigned char ip[4] = {127, 0, 0, 1};
	memcpy(&client->server_addr.sin_addr.s_addr, ip, 4);

	unsigned char data[16] = {0};
	netclient_send(client, &client->server_addr, data, sizeof(data));
}

void netclient_send(NetClient *client, const struct sockaddr_in *addr, const unsigned char *data, size_t len) {
	ssize_t bytes = sendto(client->socket, (const char *)data, len, 0, (const struct sockaddr *)addr, sizeof(*addr));
	if(bytes < 0) {
		log_error("client", "failed to send: %s", strerror(errno));
		return;
	}
	log_info("client", "sent %ld bytes", bytes);
}

void netclient_send_server(NetClient *client, const unsigned char *data, size_t len) {
	netclient_send(client, &client->server_addr, data, len);
}

ssize_t netclient_recv(NetClient *client, unsigned char *buf, size_t buf_len) {
	struct sockaddr_in peer_addr;
	socklen_t len = sizeof(peer_addr);
	errno = 0;
	ssize_t bytes = recvfrom(
		client->socket,
		buf,
		buf_len,
		0,
		(struct sockaddr *)&peer_addr,
		&len);
	if(bytes < 0) {
		if(errno == EWOULDBLOCK) {
			return 0;
		}
		log_error("client", "network error: %s", strerror(errno));
		return -1;
	}
	if(bytes == 0) {
		return 0;
	}

	if(memcmp(&peer_addr, &client->server_addr, sizeof(client->server_addr)) != 0) {
		log_warn("client", "dropping incoming udp packet from ip different than the desired server");
		return -1;
	}

	char addrstr[64];
	addr_to_str(&peer_addr, addrstr, sizeof(addrstr));
	log_info("client", "got %ld bytes from %s", bytes, addrstr);

	char hex[2048];
	str_hex(hex, sizeof(hex), buf, bytes);
	log_info("client", " %s", hex);
	return bytes;
}
