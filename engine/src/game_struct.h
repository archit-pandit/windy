#pragma once

#include "core/application.h"

// represents what a "game" will look like to the engine.
// called for creation by the application
typedef struct game {
    application_config config;

    b8 (*init)(struct game* game_instance);
    b8 (*update)(struct game* game_instance, f32 delta_time);
    b8 (*render)(struct game* game_instance, f32 delta_time);

    void (*on_resize)(struct game* game_instance, u32 width, u32 height);

    void *state;
} game;