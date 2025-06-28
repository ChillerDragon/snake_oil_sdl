#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <shared/logger.h>
#include <shared/system.h>

#include "server_state.h"

void server_init(ServerState *server) {
	server->socket = socket(AF_INET, SOCK_DGRAM, 0);
	if(server->socket < 0) {
		log_error("server", "failed to create socket");
		return;
	}

	server->addr.sin_family = AF_INET;
	server->addr.sin_port = htons(8303);
	char ip[4] = {127, 0, 0, 1};
	memcpy(&server->addr.sin_addr.s_addr, ip, 4);

	errno = 0;
	int err = bind(server->socket, (struct sockaddr *)&server->addr, sizeof(server->addr));
	if(err) {
		close(server->socket);
		log_error("server", "failed to bind: %s", strerror(errno));
		return;
	}

	int broadcast = 1;
	setsockopt(server->socket, SOL_SOCKET, SO_BROADCAST, (const char *)&broadcast, sizeof(broadcast));

	int recvsize = 65536;
	setsockopt(server->socket, SOL_SOCKET, SO_RCVBUF, (char *)&recvsize, sizeof(recvsize));

	unsigned long mode = 1;
	ioctl(server->socket, FIONBIO, &mode);
}

void server_tick(ServerState *server) {
	struct sockaddr_in peer_addr;
	socklen_t len = sizeof(peer_addr);
	errno = 0;
	ssize_t bytes = recvfrom(
		server->socket,
		server->net_in_buf,
		sizeof(server->net_in_buf),
		0,
		(struct sockaddr *)&peer_addr,
		&len);
	if(bytes < 0) {
		// this is spamming idk why
		if(errno == 11) {
			return;
		}
		log_error("server", "network error: %s", strerror(errno));
		return;
	}
	if(bytes == 0) {
		return;
	}

	char addrstr[64];
	addr_to_str(&peer_addr, addrstr, sizeof(addrstr));
	log_info("server", "got %ld bytes from %s", bytes, addrstr);

	char hex[2048];
	str_hex(hex, sizeof(hex), server->net_in_buf, bytes);
	log_info("server", " %s", hex);
}

int main() {
	log_info("server", "starting ...");

	ServerState server;
	server_init(&server);

	while(1) {
		server_tick(&server);
	}
}
