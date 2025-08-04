#include "messages.h"
#include "game/character.h"

int host_to_net_int(int val) {
#if __BYTE_ORDER == __LITTLE_ENDIAN
#elif __BYTE_ORDER == __BIG_ENDIAN
#error "big endian not implemented yet"
#endif
	return val;
}

int net_to_host_int(int val) {
#if __BYTE_ORDER == __LITTLE_ENDIAN
#elif __BYTE_ORDER == __BIG_ENDIAN
#error "big endian not implemented yet"
#endif
	return val;
}

size_t msg_pack_input(const MsgInput *input, unsigned char *buf, size_t buf_len) {
	buf[0] = MSG_INPUT;
	MsgInput *msg = (MsgInput *)(buf + 1);
	msg->direction = input->direction;
	return sizeof(MsgInput) + 1;
}

size_t msg_pack_character(const MsgCharacter *character, unsigned char *buf, size_t buf_len) {
	buf[0] = MSG_CHARACTER;
	MsgCharacter *msg = (MsgCharacter *)(buf + 1);
	msg->client_id = character->client_id;
	msg->x = host_to_net_int(character->x);
	msg->y = host_to_net_int(character->y);
	return sizeof(MsgCharacter) + 1;
}

void msg_unpack_input(MsgInput *input, const unsigned char *buf, size_t buf_len) {
	MsgInput *msg = (MsgInput *)buf;
	input->direction = msg->direction;
}

void msg_unpack_character(MsgCharacter *character, const unsigned char *buf, size_t buf_len) {
	MsgCharacter *msg = (MsgCharacter *)buf;
	character->client_id = msg->client_id;
	character->x = net_to_host_int(msg->x);
	character->y = net_to_host_int(msg->y);
}
