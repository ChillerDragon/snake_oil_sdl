#pragma once

#include <game/character.h>
#include <game/pos.h>

typedef struct {
	Character *character;
} Player;

Player *player_new();
void player_delete(Player *player);
