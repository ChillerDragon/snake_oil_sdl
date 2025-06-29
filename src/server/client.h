#pragma once

#include <netinet/in.h>

typedef struct {
	int client_id;
	struct sockaddr_in addr;
} Client;

Client *client_new(int client_id);
void client_delete(Client *client);
