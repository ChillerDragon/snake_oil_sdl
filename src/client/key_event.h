#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_scancode.h>

#include "game.h"

SDL_AppResult handle_key_event(Game *game, SDL_Scancode key_code);
