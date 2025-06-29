#include "player.h"
#include "game/character.h"

#include <stddef.h>
#include <stdlib.h>

Player *player_new() {
	Player *player = malloc(sizeof(Player));
	player->character = character_new();
	return player;
}

void player_delete(Player *player) {
	if(player->character)
		character_delete(player->character);
	player->character = NULL;
	free(player);
}
