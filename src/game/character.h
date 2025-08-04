#pragma once

#include <game/pos.h>
#include <protocol/messages.h>

typedef struct {
	int client_id;
	int height;
	int width;
	Pos pos;
	MsgInput input;
} Character;

Character *character_new(int client_id);
void character_delete(Character *character);
void character_move_right(Character *character);
void character_move_left(Character *character);
