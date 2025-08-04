#pragma once

#include <game/character.h>
#include <game/input.h>

#include <stddef.h>

enum {
	MSG_INPUT,
	MSG_CHARACTER,
};

typedef struct {
	unsigned char direction;
} MsgInput;

typedef struct {
	unsigned char client_id;
	int x;
	int y;
} MsgCharacter;

void msg_pack_input(const Input *input, unsigned char *buf, size_t buf_len);
size_t msg_pack_character(const Character *character, unsigned char *buf, size_t buf_len);

void msg_unpack_input(Input *input, const unsigned char *buf, size_t buf_len);
void msg_unpack_character(Character *character, const unsigned char *buf, size_t buf_len);
