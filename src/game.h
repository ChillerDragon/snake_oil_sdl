#pragma once

typedef struct {
} Game;

void game_init(Game *game);
void game_tick(Game *game);
void game_render(Game *game);
