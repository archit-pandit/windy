#include "application.h"
#include "platform/platform.h"
#include "logger.h"

typedef struct application_state {
    game* game_instance;
    b8 is_running;
    b8 is_suspended; // state where app should not be doing tasks, ex. minimized, etc.

    platform_state platform;

    i16 width;
    i16 height;
    
    f64 last_time; // needed for game update
} application_state;

static b8 is_init = FALSE;
static application_state app_state;

b8 application_create(game* game_instance) {
    if (is_init) {
        WINDY_ERROR("application_create called more than once!! Only one application instance allowed!");
        return FALSE;
    }

    app_state.game_instance = game_instance;

    // Init all subsystems
    init_logging();

    // Test logging functionality
    // TODO: remove
    WINDY_FATAL("test: %i", 0);
    WINDY_ERROR("test: %i", 1);
    WINDY_WARNING("test: %i", 2);
    WINDY_INFO("test: %i", 3);
    WINDY_DEBUG("test: %i", 4);
    WINDY_TRACE("test: %i", 5);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if (!platform_startup(&app_state.platform, 
                          game_instance->config.name, 
                          game_instance->config.start_pos_x, 
                          game_instance->config.start_pos_y, 
                          game_instance->config.start_width, 
                          game_instance->config.start_height)) {
        return FALSE;
    }

    // try to initalize the game
    if (!app_state.game_instance->init(app_state.game_instance)) {
        WINDY_FATAL("Game failed to initialize");
        return FALSE;
    }

    // foundation for window resizing
    app_state.game_instance->on_resize(app_state.game_instance, app_state.width, app_state.height);

    is_init = TRUE;
    return TRUE;
}

b8 application_run() {
    while (app_state.is_running) {
        if (!platform_pump_msgs(&app_state.platform)) {
            app_state.is_running = FALSE;
        }

        if (!app_state.is_suspended) {
            if (!app_state.game_instance->update(app_state.game_instance, (f32)0)) {
                WINDY_FATAL("Game update failed! Aborting!");
                app_state.is_running = FALSE;
                break;
            }

            if (!app_state.game_instance->render(app_state.game_instance, (f32)0)) {
                WINDY_FATAL("Game render failed! Aborting!");
                app_state.is_running = FALSE;
                break;
            }
        }
    }

    // assign just incase we break without assigning is_running
    app_state.is_running = FALSE;

    platform_shutdown(&app_state.platform);

    return TRUE;
}