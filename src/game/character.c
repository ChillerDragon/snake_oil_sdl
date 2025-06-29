#include <stdlib.h>

#include "character.h"

Character *character_new() {
	Character *character = malloc(sizeof(Character));
	character->height = 100;
	character->width = 100;
	character->pos.x = 0;
	character->pos.y = 0;
	return character;
}

void character_delete(Character *character) {
	free(character);
}

void character_move_right(Character *character) {
	character->pos.x++;
}

void character_move_left(Character *character) {
	character->pos.x--;
}
