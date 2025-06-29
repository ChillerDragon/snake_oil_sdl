#pragma once

#include <game/input.h>
#include <game/pos.h>

typedef struct {
	int client_id;
	int height;
	int width;
	Pos pos;
	Input input;
} Character;

Character *character_new(int client_id);
void character_delete(Character *character);
void character_move_right(Character *character);
void character_move_left(Character *character);
