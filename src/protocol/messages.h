#pragma once

#include <stddef.h>
#include <stdint.h>

enum {
	MSG_INPUT,
	MSG_CHARACTER,
	MSG_GAME_INFO,
};

typedef struct {
	int direction;
} MsgInput;

typedef struct {
	unsigned char client_id;
	int x;
	int y;
} MsgCharacter;

typedef struct {
	uint64_t server_tick;
} MsgGameInfo;

size_t msg_pack_input(const MsgInput *input, unsigned char *buf, size_t buf_len);
size_t msg_pack_character(const MsgCharacter *character, unsigned char *buf, size_t buf_len);
size_t msg_pack_game_info(const MsgGameInfo *game_info, unsigned char *buf, size_t buf_len);

void msg_unpack_input(MsgInput *input, const unsigned char *buf, size_t buf_len);
void msg_unpack_character(MsgCharacter *character, const unsigned char *buf, size_t buf_len);
void msg_unpack_game_info(MsgGameInfo *game_info, const unsigned char *buf, size_t buf_len);
