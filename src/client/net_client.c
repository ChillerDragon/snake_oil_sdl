#include <errno.h>
#include <netinet/in.h>
#include <stddef.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <shared/logger.h>

#include "net_client.h"

void netclient_init(NetClient *client) {
	client->socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(client->socket < 0) {
		log_error("client", "failed to create socket");
		return;
	}

	client->addr.sin_family = AF_INET;
	client->addr.sin_port = htons(8303);
	char ip[4] = {127, 0, 0, 1};
	memcpy(&client->addr.sin_addr.s_addr, ip, 4);

	int err = bind(client->socket, (struct sockaddr *)&client->addr, sizeof(client->addr));
	if(err) {
		close(client->socket);
		log_error("client", "failed to bind");
		return;
	}

	int broadcast = 1;
	setsockopt(client->socket, SOL_SOCKET, SO_BROADCAST, (const char *)&broadcast, sizeof(broadcast));

	int recvsize = 65536;
	setsockopt(client->socket, SOL_SOCKET, SO_RCVBUF, (char *)&recvsize, sizeof(recvsize));

	unsigned long mode = 1;
	ioctl(client->socket, FIONBIO, &mode);
}

void netclient_connect(NetClient *client, const char *addr) {
	// TODO: actually parse the address

	client->server_addr.sin_family = AF_INET;
	client->server_addr.sin_port = 8303;
	unsigned char ip[4] = {127, 0, 0, 1};
	memcpy(&client->server_addr.sin_addr.s_addr, ip, 4);
}

void netclient_send(NetClient *client, const struct sockaddr_in *addr, const unsigned char *data, size_t len) {
	log_info("client", "socket %d", client->socket);

	ssize_t bytes = sendto(client->socket, (const char *)data, len, 0, (const struct sockaddr *)addr, sizeof(*addr));
	if(bytes < 0) {
		log_error("client", "failed to send: %s", strerror(errno));
		return;
	}
	log_info("client", "sent %ld bytes", bytes);
}

void netclient_tick(NetClient *client) {
	unsigned char data[16] = {0};
	netclient_send(client, &client->server_addr, data, sizeof(data));
}
