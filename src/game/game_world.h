#pragma once

#include <game/character.h>
#include <game/player.h>
#include <protocol/protocol.h>

typedef struct {
	// list of all character in the world
	// if the character is not online or currently dead
	// it is a NULL pointer
	Character *characters[MAX_CLIENTS];
} GameWorld;

void gameworld_init(GameWorld *world);
void gameworld_shutdown(GameWorld *world);
void gameworld_tick(GameWorld *world);
void gameworld_add_character(GameWorld *world, Character *character, int client_id);
void gameworld_remove_character(GameWorld *world, int client_id);
