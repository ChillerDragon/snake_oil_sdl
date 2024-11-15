#include <SDL3/SDL_render.h>

#include "game.h"
#include "player.h"

void game_init(Game *game) {
	game->players[0] = player_new();
	game->players[1] = player_new();
	game->players[2] = player_new();
	game->players[2]->pos.y = 200;
}

void game_shutdown(Game *game) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		player_delete(game->players[i]);
	}
}

void game_tick(Game *game) {}

void game_render(Game *game, SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Player *player = game->players[i];
		if(!player)
			continue;

		player_draw(player, renderer);
	}
	SDL_RenderPresent(renderer);
}
