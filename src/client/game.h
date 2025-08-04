#pragma once

#include <SDL3/SDL_render.h>

#include <client/net_client.h>
#include <game/game_world.h>
#include <game/player.h>
#include <protocol/protocol.h>

#include "camera.h"

typedef struct {
	GameWorld *world;

	// id of our own player
	// will be 0 at all times as long as the game is offline
	// once multiplayer is added this will be sent by the server
	// can be used to index the Game.players array.
	int client_id;

	// follows our own player by default
	// holds the position of the view port
	// and the zoom level
	Camera camera;

	MsgInput input;
} Game;

void game_init(Game *game);
void game_shutdown(Game *game);
void game_tick(Game *game, NetClient *client);
void game_on_data(Game *game, const unsigned char *data, size_t data_len);
void game_on_msg_character(Game *game, const unsigned char *data, size_t data_len);
void game_render(Game *game, SDL_Renderer *renderer, SDL_Window *window);
