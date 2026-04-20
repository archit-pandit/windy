#pragma once

#include "defines.h"
#include "game_struct.h"

// Application Config
typedef struct application_config {
    // window start position, if applicable
    i16 start_pos_x;
    i16 start_pos_y;

    // window start width/height, if applicable
    i16 start_width;
    i16 start_height;

    // application name for window, if applicable
    char* name;
} application_config;

WINDY_API b8 application_create(game* game_instance);
WINDY_API b8 application_run();