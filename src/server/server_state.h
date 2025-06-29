#pragma once

#include <netinet/in.h>

#include <game/game_world.h>
#include <protocol/protocol.h>
#include <server/client.h>

typedef struct {
	struct sockaddr_in addr;
	int socket;
	unsigned char net_in_buf[NET_MAX_PACKETSIZE];

	GameWorld *world;
	Client *clients[MAX_CLIENTS];
} ServerState;
