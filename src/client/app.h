#pragma once

#include "app_state.h"

void app_init(AppState *as);
void app_tick(AppState *as);
void app_render(AppState *as);
void app_shutdown(AppState *as);
