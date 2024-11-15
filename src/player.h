#pragma once

#include <SDL3/SDL_render.h>

#include "camera.h"
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
void player_draw(Player *player, Camera *camera, SDL_Renderer *renderer);
