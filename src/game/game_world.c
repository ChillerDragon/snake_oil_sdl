#include <string.h>

#include <game/character.h>
#include <game/player.h>
#include <protocol/protocol.h>

#include "game_world.h"

void gameworld_init(GameWorld *world) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		world->characters[i] = NULL;
	}
}

void gameworld_shutdown(GameWorld *world) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Character *character = world->characters[i];
		if(!character)
			continue;

		character_delete(character);
		character = NULL;
	}
}

void gameworld_tick(GameWorld *world) {
	for(int i = 0; i < MAX_CLIENTS; i++) {
		Character *character = world->characters[i];
		if(!character)
			continue;
	}
}

void gameworld_add_character(GameWorld *world, Character *character, int client_id) {
	world->characters[client_id] = character;
}

void gameworld_remove_character(GameWorld *world, int client_id) {
	character_delete(world->characters[client_id]);
	world->characters[client_id] = NULL;
}
