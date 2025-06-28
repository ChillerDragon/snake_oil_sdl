#pragma once

#include <netinet/in.h>

#include <protocol/protocol.h>

typedef struct {
	int socket;
	struct sockaddr_in addr;
	struct sockaddr_in server_addr;
	unsigned char net_in_buf[NET_MAX_PACKETSIZE];
} NetClient;

void netclient_init(NetClient *client);
void netclient_connect(NetClient *client, const char *addr);
void netclient_send(NetClient *client, const struct sockaddr_in *addr, const unsigned char *data, size_t len);
void netclient_tick(NetClient *client);
