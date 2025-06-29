#include <stdlib.h>

#include "client.h"

Client *client_new(int client_id) {
	Client *client = malloc(sizeof(Client));
	client->client_id = client_id;
	return client;
}

void client_delete(Client *client) {
	free(client);
}
