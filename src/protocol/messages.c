#include "messages.h"
#include "game/character.h"

void msg_pack_input(const Input *input, unsigned char *buf, size_t buf_len) {
	buf[0] = MSG_INPUT;
	buf[1] = input->direction;
}

size_t msg_pack_character(const Character *character, unsigned char *buf, size_t buf_len) {
	buf[0] = MSG_CHARACTER;
	MsgCharacter *msg = (MsgCharacter *)(buf + 1);
	msg->client_id = character->client_id;
	msg->x = character->pos.x;
	msg->y = character->pos.y;
	return sizeof(MsgCharacter) + 1;
}

void msg_unpack_input(Input *input, const unsigned char *buf, size_t buf_len) {
	input->direction = buf[0];
}

void msg_unpack_character(Character *character, const unsigned char *buf, size_t buf_len) {
	MsgCharacter *msg = (MsgCharacter *)buf;
	character->client_id = msg->client_id;
	character->pos.x = msg->x;
	character->pos.y = msg->y;
}
