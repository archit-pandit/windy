#pragma once

#include "core/application.h"
#include "core/logger.h"
#include "game_struct.h"

// function to create a game, defined externally outside entry.c (main.c)
extern b8 create_game(game* game_out);

// Main entry point of the application
int main(void) {
    game game_instance;

    if (!create_game(&game_instance)) {
        WINDY_FATAL("Could not create game!");
        return -1;
    }

    // ensure game instance function pointers exist
    if (!game_instance.render ||
        !game_instance.update ||
        !game_instance.init ||
        !game_instance.on_resize) {
        WINDY_FATAL("game_instance function pointers cannot be NULL and must be assigned!!");
        return -2;
    }

    // initializes the application
    if (!application_create(&game_instance)) {
        WINDY_INFO("Application failed to create!");
        return 1;
    }

    // begins game loop
    if (!application_run()) {
        WINDY_INFO("Application did not shutdown gracefully");
        return 2;
    }

    return 0;
};