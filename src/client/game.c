#include <stdlib.h>

#include <SDL3/SDL_render.h>

#include <client/game_world.h>
#include <game/character.h>
#include <game/game_world.h>
#include <game/player.h>
#include <protocol/protocol.h>
#include <shared/logger.h>

#include "camera.h"
#include "game.h"
#include "protocol/messages.h"

void game_init(Game *game) {
	game->camera.pos.x = 0;
	game->camera.pos.y = 0;
	game->camera.zoom = 1;

	game->world = malloc(sizeof(GameWorld));
	gameworld_init(game->world);

	// for(int i = 1; i < MAX_CLIENTS; i++) {
	// 	game->players[i] = player_new();
	// 	game->players[i]->pos.y = i;
	// 	game->players[i]->pos.x = (i % 2) ? i : -i;
	// }
}

void game_shutdown(Game *game) {
	gameworld_shutdown(game->world);
}

void game_tick(Game *game) {
}

void game_on_data(Game *game, const unsigned char *data, const size_t data_len) {
	log_info("game", "got data");

	switch(data[0]) {
	case MSG_CHARACTER:
		game_on_msg_character(game, data + 1, data_len - 1);
		break;
	default:
		log_error("game", "unknown msg %d", data[0]);
		break;
	};
}

void game_on_msg_character(Game *game, const unsigned char *data, const size_t data_len) {
	MsgCharacter *msg = (MsgCharacter *)data;

	if(msg->client_id < 0 || msg->client_id >= MAX_CLIENTS) {
		log_error("game", "invalid client id %d", msg->client_id);
		return;
	}

	Character *character = game->world->characters[msg->client_id];
	if(!character) {
		character = character_new(msg->client_id);
	}
	character->pos.x = (int)msg->x;
	character->pos.y = (int)msg->y;
	game->world->characters[msg->client_id] = character;
}

void game_render(Game *game, SDL_Renderer *renderer) {
	GameWorld *world = game->world;

	// follow own player
	Character *own_character = world->characters[game->client_id];
	if(own_character)
		camera_set_pos(&game->camera, own_character->pos);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	gameworld_draw(world, &game->camera, renderer);
}
