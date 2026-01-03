#include <core/logger.h>

int main(void) {
    WFATAL("test: %i", 0);
    WERROR("test: %i", 1);
    WWARNING("test: %i", 2);
    WINFO("test: %i", 3);
    WDEBUG("test: %i", 4);
    WTRACE("test: %i", 5);
    
    return 0;
}