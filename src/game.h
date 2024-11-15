#pragma once

#include <SDL3/SDL_render.h>

#include "enums.h"
#include "player.h"

typedef struct {
	Player *players[MAX_CLIENTS];
} Game;

void game_init(Game *game);
void game_shutdown(Game *game);
void game_tick(Game *game);
void game_render(Game *game, SDL_Renderer *renderer);
