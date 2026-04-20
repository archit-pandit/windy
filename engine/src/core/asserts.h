#pragma once

#include "defines.h"

// disbaled assertions by commenting out this line
#define WINDY_ASSERTIONS_ENABLED

#ifdef WINDY_ASSERTIONS_ENABLED
    #if _MSC_VER // if using visual studio compiler
        #include <intrin.h>
        #define debugBreak() __debugbreak()
    #else
        #define debugBreak() __builtin_trap()
    #endif

    WINDY_API void report_assert_failure(const char* exp, const char* msg, const char* file, i32 line);

    // exp must eval to bool
    #define WINDY_ASSERT(exp) {                                              \
        if (exp) {                                                      \
        } else {                                                        \
            report_assert_failure(#exp, "", __FILE__, __LINE__);        \
            debugBreak();                                               \
        }                                                               \
    }

    #define WINDY_ASSERT_MSG(exp, msg) {                                     \
        if (exp) {                                                      \
        } else {                                                        \
            report_assert_failure(#exp, msg, __FILE__, __LINE__);       \
            debugBreak();                                               \
        }                                                               \
    }

    #ifdef _DEBUG
        #define WINDY_ASSERT_DEBUG(exp) {                                    \
            if (exp) {                                                  \
            } else {                                                    \
                report_assert_failure(#exp, "", __FILE__, __LINE__);    \
                debugBreak();                                           \
            }                                                           \
        }
    #else
        #define WINDY_ASSERT_DEBUG(exp)  // does nothing
    #endif
#else
    #define WINDY_ASSERT(exp);           // does nothing
    #define WINDY_ASSERT_MSG(exp, msg);  // does nothing
    #define WINDY_ASSERT_DEBUG(exp);     // does nothing
#endif