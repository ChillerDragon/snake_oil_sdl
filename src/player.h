#pragma once

#include <SDL3/SDL_render.h>

#include "pos.h"

typedef struct {
	int height;
	int width;
	Pos pos;
} Player;

Player *player_new();
void player_delete(Player *player);
void player_move_right(Player *player);
void player_move_left(Player *player);
void player_draw(Player *player, SDL_Renderer *renderer);
