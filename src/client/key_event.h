#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_scancode.h>

#include "game.h"

SDL_AppResult handle_key_event_down(Game *game, SDL_Scancode key_code);
SDL_AppResult handle_key_event_up(Game *game, SDL_Scancode key_code);
