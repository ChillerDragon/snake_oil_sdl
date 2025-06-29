#include "messages.h"

void msg_pack_input(const Input *input, unsigned char *buf, size_t buf_len) {
	buf[0] = MSG_INPUT;
	buf[1] = input->direction;
}

void msg_pack_character(const Character *character, unsigned char *buf, size_t buf_len) {
	buf[0] = MSG_CHARACTER;
	buf[1] = character->pos.x;
	buf[2] = character->pos.y;
}

void msg_unpack_input(Input *input, const unsigned char *buf, size_t buf_len) {
	input->direction = buf[0];
}

void msg_unpack_character(Character *character, const unsigned char *buf, size_t buf_len) {
	character->pos.x = buf[0];
	character->pos.y = buf[1];
}
