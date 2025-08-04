#pragma once

#include <netinet/in.h>

#include <game/character.h>
#include <server/server_state.h>

void server_init(ServerState *server);
void server_init_network(ServerState *server);
void server_init_game(ServerState *server);
void server_shutdown(ServerState *server);
void server_send(ServerState *server, const struct sockaddr_in *addr, const unsigned char *data, size_t len);
void server_tick(ServerState *server);
void server_read_network(ServerState *server);
void server_on_msg_input(ServerState *server, Client *client, unsigned char *data, size_t data_len);
void server_send_game(ServerState *server);
void server_send_game_to_client(ServerState *server, Client *client);
int server_next_client_id(ServerState *server);
Client *server_find_client_by_addr(ServerState *server, const struct sockaddr_in *addr);
void server_on_client_connect(ServerState *server, const struct sockaddr_in *addr);
