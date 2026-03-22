#pragma once

#include "defines.h"

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

WAPI b8 application_create(application_config* config);
WAPI b8 application_run();