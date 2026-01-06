#include <core/logger.h>
#include <core/asserts.h>

int main(void) {
    WFATAL("test: %i", 0);
    WERROR("test: %i", 1);
    WWARNING("test: %i", 2);
    WINFO("test: %i", 3);
    WDEBUG("test: %i", 4);
    WTRACE("test: %i", 5);

    WASSERT(1 == 0);
    return 0;
}