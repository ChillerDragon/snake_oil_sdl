#include <SDL3/SDL_render.h>

#include <game/character.h>
#include <game/player.h>
#include <protocol/protocol.h>

#include "camera.h"
#include "character.h"
#include "game.h"

void game_init(Game *game) {
	game->camera.pos.x = 0;
	game->camera.pos.y = 0;
	game->camera.zoom = 1;

	game->players[0] = player_new(1);
	game->players[1] = player_new(2);
	game->players[2] = player_new(3);
	if(game->players[2]->character)
		game->players[2]->character->pos.y = 200;

	// for(int i = 1; i < MAX_CLIENTS; i++) {
	// 	game->players[i] = player_new();
	// 	game->players[i]->pos.y = i;
	// 	game->players[i]->pos.x = (i % 2) ? i : -i;
	// }
}

void game_shutdown(Game *game) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Player *player = game->players[i];
		if(!player)
			continue;

		player_delete(player);
		player = NULL;
	}
}

void game_tick(Game *game) {
}

void game_render(Game *game, SDL_Renderer *renderer) {
	// follow own player
	if(game->players[game->client_id]) {
		Character *character = game->players[game->client_id]->character;
		if(character)
			camera_set_pos(&game->camera, character->pos);
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Player *player = game->players[i];
		if(!player)
			continue;
		if(!player->character)
			continue;

		character_draw(player->character, &game->camera, renderer);
	}
}
