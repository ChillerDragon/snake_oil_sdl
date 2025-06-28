#pragma once

#include <netinet/in.h>

#include <protocol/protocol.h>

typedef struct {
	struct sockaddr_in addr;
	int socket;
	unsigned char net_in_buf[NET_MAX_PACKETSIZE];
} ServerState;
