#pragma once

#include <SDL3/SDL_render.h>

typedef struct {
	int x;
	int y;
} Player;

Player *player_new();
void player_delete(Player *player);
void player_draw(Player *player, SDL_Renderer *renderer);
