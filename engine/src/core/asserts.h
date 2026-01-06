#pragma once

#include "defines.h"

// disbaled assertions by commenting out this line
#define WASSERTIONS_ENABLED

#ifdef WASSERTIONS_ENABLED
    #if _MSC_VER // if using visual studio compiler
        #include <intrin.h>
        #define debugBreak() __debugbreak()
    #else
        #define debugBreak() __builtin_trap()
    #endif

    WAPI void report_assert_failure(const char* exp, const char* msg, const char* file, i32 line);

    // exp must eval to bool
    #define WASSERT(exp) {                                              \
        if (exp) {                                                      \
        } else {                                                        \
            report_assert_failure(#exp, "", __FILE__, __LINE__);        \
            debugBreak();                                              \
        }                                                               \
    }

    #define WASSERT_MSG(exp, msg) {                                     \
        if (exp) {                                                      \
        } else {                                                        \
            report_assert_failure(#exp, msg, __FILE__, __LINE__);       \
            debugBreak();                                              \
        }                                                               \
    }

    #ifdef _DEBUG
        #define WASSERT_DEBUG(exp) {                                    \
            if (exp) {                                                  \
            } else {                                                    \
                report_assert_failure(#exp, "", __FILE__, __LINE__);    \
                debugBreak();                                          \
            }                                                           \
        }
    #else
        #define WASSERT_DEBUG(exp)  // does nothing
    #endif
#else
    #define WASSERT(exp);           // does nothing
    #define WASSERT_MSG(exp, msg);  // does nothing
    #define WASSERT_DEBUG(exp);     // does nothing
#endif