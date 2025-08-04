#pragma once

#include <stddef.h>

enum {
	MSG_INPUT,
	MSG_CHARACTER,
};

typedef struct {
	int direction;
} MsgInput;

typedef struct {
	unsigned char client_id;
	int x;
	int y;
} MsgCharacter;

size_t msg_pack_input(const MsgInput *input, unsigned char *buf, size_t buf_len);
size_t msg_pack_character(const MsgCharacter *character, unsigned char *buf, size_t buf_len);

void msg_unpack_input(MsgInput *input, const unsigned char *buf, size_t buf_len);
void msg_unpack_character(MsgCharacter *character, const unsigned char *buf, size_t buf_len);
