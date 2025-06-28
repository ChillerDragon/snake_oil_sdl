#pragma once

#include <SDL3/SDL_render.h>

#include "camera.h"
#include "enums.h"
#include "player.h"

typedef struct {
	// list of all players including our self
	// at index Game.client_id
	// if player with that id is not online it is a NULL pointer
	Player *players[MAX_CLIENTS];

	// id of our own player
	// will be 0 at all times as long as the game is offline
	// once multiplayer is added this will be sent by the server
	// can be used to index the Game.players array.
	int client_id;

	// follows our own player by default
	// holds the position of the view port
	// and the zoom level
	Camera camera;
} Game;

void game_init(Game *game);
void game_shutdown(Game *game);
void game_tick(Game *game);
void game_render(Game *game, SDL_Renderer *renderer);
