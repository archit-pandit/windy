#pragma once

#include "defines.h"

// disbaled assertions by commenting out this line
#define WASSERTIONS_ENABLED

#ifdef WASSERTIONS_ENABLED
    #if _MSC_VER // if using visual studio compiler
        #include <intrin.h>
        #define debug_break() __debugbreak()
    #else
        #define debug_break() __builtin_trap()
    #endif
#endif

void report_assert_fail(const char* exp, const char* msg, const char* file, i32 line);