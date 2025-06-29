#pragma once

#include <game/character.h>
#include <game/pos.h>

typedef struct {
	int client_id;
	Character *character;
} Player;

Player *player_new(int client_id);
void player_delete(Player *player);
