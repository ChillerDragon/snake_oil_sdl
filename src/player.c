#include "player.h"

#include <SDL3/SDL_stdinc.h>

Player *player_new() {
	Player *player = SDL_calloc(1, sizeof(Player));
	player->height = 100;
	player->width = 100;
	player->pos.x = 0;
	player->pos.y = 0;
	return player;
}

void player_delete(Player *player) {
	SDL_free(player);
}

void player_move_right(Player *player) {
	player->pos.x++;
}

void player_move_left(Player *player) {
	player->pos.x--;
}

void player_draw(Player *player, SDL_Renderer *renderer) {
	SDL_FRect r = {
		.w = (float)player->width,
		.h = (float)player->height,
		.x = (float)player->pos.x,
		.y = (float)player->pos.y};

	SDL_SetRenderDrawColor(renderer, 0, 128, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &r);
}
