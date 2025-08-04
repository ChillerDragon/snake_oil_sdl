#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <shared/logger.h>
#include <shared/system.h>

#include "game/character.h"
#include "game/game_world.h"
#include "protocol/messages.h"
#include "protocol/protocol.h"
#include "server/client.h"
#include "server_state.h"

#include "server.h"

void server_init(ServerState *server) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		server->clients[i] = NULL;
	}
	server_init_network(server);
	server_init_game(server);
}

void server_init_network(ServerState *server) {
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

void server_init_game(ServerState *server) {
	server->world = malloc(sizeof(GameWorld));
	gameworld_init(server->world);

	server->tick = 0;
	GameWorld *world = server->world;
}

void server_shutdown(ServerState *server) {
	close(server->socket);
	gameworld_shutdown(server->world);

	for(int i = 0; i < MAX_CLIENTS; i++) {
		Client *client = server->clients[i];
		if(!client)
			continue;

		client_delete(client);
	}
}

void server_send(ServerState *server, const struct sockaddr_in *addr, const unsigned char *data, size_t len) {
	ssize_t bytes = sendto(server->socket, (const char *)data, len, 0, (const struct sockaddr *)addr, sizeof(*addr));
	if(bytes < 0) {
		log_error("server", "failed to send: %s", strerror(errno));
		return;
	}
	// log_info("server", "sent %ld bytes", bytes);
}

void server_tick(ServerState *server) {
	server->tick++;
	server_read_network(server);
	server_send_game(server);

	// just to test rendering for now
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Character *character = server->world->characters[i];
		if(!character)
			continue;

		Client *client = server->clients[i];

		if(server->tick % 50 == 0) {
			// TODO: send game info to client to debug tick sync
		}

		if(client->input.direction == 1) {
			character->pos.x++;
		} else if(client->input.direction == -1) {
			character->pos.x--;
		}

		// if(client->bounced) {
		// 	character->pos.x--;
		// 	if(character->pos.x < 2)
		// 		client->bounced = 0;
		// } else {
		// 	character->pos.x++;
		// 	if(character->pos.x > 200)
		// 		client->bounced = 1;
		// }

		log_info("server", "cid=%d x=%d", i, character->pos.x);
	}
}

void server_read_network(ServerState *server) {
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
		if(errno == EWOULDBLOCK) {
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

	Client *client = server_find_client_by_addr(server, &peer_addr);
	if(!client) {
		// TODO: check if the data sent is a proper connect msg :D
		server_on_client_connect(server, &peer_addr);
	} else {
		switch(server->net_in_buf[0]) {
		case MSG_INPUT:
			server_on_msg_input(server, client, server->net_in_buf + 1, bytes - 1);
			break;
		default:
			log_error("game", "unknown msg %d", server->net_in_buf[0]);
			break;
		};
	}
}

void server_on_msg_input(ServerState *server, Client *client, unsigned char *data, size_t data_len) {
	if(data_len < sizeof(MsgInput)) {
		log_error("server", "input msg too short");
		return;
	}

	MsgInput msg;
	msg_unpack_input(&msg, data, data_len);

	client->input.direction = msg.direction;
}

void server_send_game(ServerState *server) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Client *client = server->clients[i];
		if(!client)
			continue;

		server_send_game_to_client(server, client);
	}
}

void server_send_game_to_client(ServerState *server, Client *client) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Character *character = server->world->characters[i];
		if(!character)
			continue;

		unsigned char data[128];
		MsgCharacter msg;
		msg.client_id = character->client_id;
		msg.x = character->pos.x;
		msg.y = character->pos.y;
		size_t data_len = msg_pack_character(&msg, data, sizeof(data));

		// log_info("server", "packing character cid=%d x=%d y=%d", character->client_id, character->pos.x, character->pos.y);
		// char hex[128];
		// str_hex(hex, sizeof(hex), data, data_len);
		// log_info("server", " %s", hex);

		server_send(server, &client->addr, data, data_len);
	}
}

// TODO: not sure about client ids yet
//       having reusable client ids is nice for low network bandwith with reconnects
//       but having unique client ids is nice to aovid conflicts when client ids get inherited
int server_next_client_id(ServerState *server) {
	// reusable for now ..
	for(int i = 0; i < MAX_CLIENTS; i++) {
		if(!server->clients[i])
			return i;
	}
	return 0;
}

Client *server_find_client_by_addr(ServerState *server, const struct sockaddr_in *addr) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Client *client = server->clients[i];
		if(!client)
			continue;
		if(memcmp(&client->addr, addr, sizeof(*addr)) != 0)
			continue;

		return client;
	}
	return NULL;
}

void server_on_client_connect(ServerState *server, const struct sockaddr_in *addr) {
	int client_id = server_next_client_id(server);
	Client *client = client_new(client_id);
	client->addr = *addr;
	server->clients[client_id] = client;

	char addrstr[64];
	addr_to_str(addr, addrstr, sizeof(addrstr));
	log_info("server", "player joined with cid=%d and addr=%s", client_id, addrstr);

	server->world->characters[client_id] = character_new(client_id);
	server->world->characters[client_id]->pos.x = 200 * client_id;
}
