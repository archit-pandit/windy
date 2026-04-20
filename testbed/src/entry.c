#include "game.h"
#include <entry.h>

// definition of function to create game
b8 create_game(game* game_out) {
    game_out->config.start_pos_x = 100;
    game_out->config.start_pos_y = 100;
    game_out->config.start_width = 1280;
    game_out->config.start_height = 720;
    game_out->config.name = "Test";

    game_out->update
}