#include "player.h"

#include <SDL3/SDL_stdinc.h>

Player *player_new() {
	Player *player = SDL_calloc(1, sizeof(Player));
	player->x = 0;
	player->y = 0;
	return player;
}

void player_draw(Player *player, SDL_Renderer *renderer) {
	SDL_FRect r = {
		.w = 10,
		.h = 10,
		.x = (float)player->x,
		.y = (float)player->y};

	SDL_SetRenderDrawColor(renderer, 0, 128, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &r);
	SDL_RenderPresent(renderer);
}
