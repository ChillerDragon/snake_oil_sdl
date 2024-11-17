#include <SDL3/SDL_render.h>

#include "camera.h"
#include "enums.h"
#include "game.h"
#include "player.h"

void game_init(Game *game) {
	game->camera.pos.x = 0;
	game->camera.pos.y = 0;
	game->camera.zoom = 1;

	game->players[0] = player_new();
	// game->players[1] = player_new();
	// game->players[2] = player_new();
	// game->players[2]->pos.y = 200;

	for(int i = 1; i < MAX_CLIENTS; i++) {
		game->players[i] = player_new();
		game->players[i]->pos.y = i;
		game->players[i]->pos.x = (i % 2) ? i : -i;
	}
}

void game_shutdown(Game *game) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		player_delete(game->players[i]);
	}
}

void game_tick(Game *game) {
}

void game_render(Game *game, SDL_Renderer *renderer) {
	// follow own player
	camera_set_pos(&game->camera, game->players[game->client_id]->pos);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Player *player = game->players[i];
		if(!player)
			continue;

		player_draw(player, &game->camera, renderer);
	}
}
