#include "player.h"

#include <stdlib.h>

Player *player_new() {
	Player *player = malloc(sizeof(Player));
	player->height = 100;
	player->width = 100;
	player->pos.x = 0;
	player->pos.y = 0;
	return player;
}

void player_delete(Player *player) {
	free(player);
}

void player_move_right(Player *player) {
	player->pos.x++;
}

void player_move_left(Player *player) {
	player->pos.x--;
}
