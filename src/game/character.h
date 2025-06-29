#pragma once

#include <game/pos.h>

typedef struct {
	int height;
	int width;
	Pos pos;
} Character;

Character *character_new();
void character_delete(Character *character);
void character_move_right(Character *character);
void character_move_left(Character *character);
