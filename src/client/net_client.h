#pragma once

#include <netinet/in.h>
#include <stdio.h>

#include <protocol/protocol.h>

typedef struct {
	int socket;
	struct sockaddr_in addr;
	struct sockaddr_in server_addr;
	unsigned char net_in_buf[NET_MAX_PACKETSIZE];
	uint64_t last_send;
} NetClient;

void netclient_init(NetClient *client);
void netclient_connect(NetClient *client, const char *addr);
void netclient_send(NetClient *client, const struct sockaddr_in *addr, const unsigned char *data, size_t len);
void netclient_send_server(NetClient *client, const unsigned char *data, size_t len);
// checks for new incoming data from the server
// and writes it into ``buf``
// returns amount of bytes received from server or -1 on error
ssize_t netclient_recv(NetClient *client, unsigned char *buf, size_t buf_len);
