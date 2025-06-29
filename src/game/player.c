#include "player.h"
#include "game/character.h"

#include <stddef.h>
#include <stdlib.h>

Player *player_new(int client_id) {
	Player *player = malloc(sizeof(Player));
	player->client_id = client_id;
	player->character = character_new(client_id);
	return player;
}

void player_delete(Player *player) {
	if(player->character)
		character_delete(player->character);
	player->character = NULL;
	free(player);
}
