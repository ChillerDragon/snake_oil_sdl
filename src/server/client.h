#pragma once

#include <netinet/in.h>
#include <protocol/messages.h>

typedef struct {
	int client_id;
	struct sockaddr_in addr;

	MsgInput input;

	int bounced;
} Client;

Client *client_new(int client_id);
void client_delete(Client *client);
