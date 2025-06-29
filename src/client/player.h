#pragma once

#include <SDL3/SDL_render.h>

#include <game/player.h>
#include <game/pos.h>

#include "camera.h"

void player_draw(Player *player, Camera *camera, SDL_Renderer *renderer);
