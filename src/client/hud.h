#pragma once

#include <SDL3/SDL_render.h>

#include <client/game.h>

void hud_draw(Game *game, SDL_Renderer *renderer, const char *fps_text);
