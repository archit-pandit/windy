#pragma once

#include "defines.h"

typedef struct platform_state {
    void* internal_state;
} platform_state;

WAPI b8 platform_startup (
    platform_state* p_state,
    const char* app_name,
    i32 x,
    i32 y,
    i32 width,
    i32 height
);

WAPI void platform_shutdown (platform_state* p_state);
WAPI b8 platform_pump_msgs(platform_state* p_state); // needs to be continously run

void* platform_allocate(u64 size, b8 aligned);
void platform_free(void* block, b8 aligned);
void* platform_zero_memory(void* block, u64 size);
void* platform_copy_memory(void* dest, const void* src, u64 size);
void* platform_set_memory(void* dest, i32 val, u64 size);

void platform_console_write(const char* msg, u8 colour);
void platform_console_write_error(const char* msg, u8 colour);

f64 platform_get_abs_time();

// Sleep on thread for passed miliseconds. Blocks main thread. NOT exported
void platform_sleep(u64 ms);