#pragma once

#include <SDL3/SDL_render.h>

#include <client/camera.h>
#include <game/game_world.h>

void gameworld_draw(GameWorld *world, Camera *camera, SDL_Renderer *renderer);
