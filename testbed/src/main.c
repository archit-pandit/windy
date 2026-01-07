#include <core/logger.h>
#include <core/asserts.h>

// TODO: temp, for testing
#include <platform/platform.h>

int main(void) {
    WFATAL("test: %i", 0);
    WERROR("test: %i", 1);
    WWARNING("test: %i", 2);
    WINFO("test: %i", 3);
    WDEBUG("test: %i", 4);
    WTRACE("test: %i", 5);

    platform_state state;
    if (platform_startup(&state, "test", 300, 300, 1280, 720)) {
        while (TRUE) {
            platform_pump_msgs(&state);
        }
    }

    platform_shutdown(&state);

    return 0;
}