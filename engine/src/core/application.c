#include "application.h"
#include "platform/platform.h"
#include "logger.h"

typedef struct application_state {
    b8 is_running;
    b8 is_suspended; // state where app should not be doing tasks, ex. minimized, etc.

    platform_state platform;

    i16 width;
    i16 height;
    
    f64 last_time; // needed for game update
} application_state;

static b8 is_init = FALSE;
static application_state app_state;

b8 application_create(application_config* config) {
    if (is_init) {
        WERROR("application_create called more than once!! Only one application instance allowed!");
        return FALSE;
    }

    // Init all subsystems
    init_logging();

    // Test logging functionality
    // TODO: remove
    WFATAL("test: %i", 0);
    WERROR("test: %i", 1);
    WWARNING("test: %i", 2);
    WINFO("test: %i", 3);
    WDEBUG("test: %i", 4);
    WTRACE("test: %i", 5);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if (!platform_startup(&app_state.platform, 
                         config->name, 
                         config->start_pos_x, 
                         config->start_pos_y, 
                         config->start_width, 
                         config->start_height)) {
        return FALSE;
    }

    is_init = TRUE;
    return TRUE;
}

b8 application_run() {
    while (app_state.is_running) {
        if (!platform_pump_msgs(&app_state.platform)) {
            app_state.is_running = FALSE;
        }
    }

    app_state.is_running = FALSE;

    platform_shutdown(&app_state.platform);

    return TRUE;
}