#pragma once
#include "defines.h"

#define LOG_WARNING_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace log for release
#if WINDY_RELEASE == 1
    #define LOG_DEBUG_ENABLED 0
    #define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level {
    LOG_LEVEL_FATAL = 0, // causes a crash
    LOG_LEVEL_ERROR = 1, // error, but continues to run
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5
} log_level;

b8 init_logging();
void close_logging();

WINDY_API void log_output(log_level lvl, const char* msg, ...);

// logs fatal message
#ifndef WINDY_FATAL
    #define WINDY_FATAL(msg, ...) log_output(LOG_LEVEL_FATAL, msg, ##__VA_ARGS__);
#endif

// logs error message
#ifndef WINDY_ERROR
    #define WINDY_ERROR(msg, ...) log_output(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__);
#endif

// logs warning message if warning logs are enabled, otherwise does nothing
#if LOG_WARNING_ENABLED == 1
    #define WINDY_WARNING(msg, ...) log_output(LOG_LEVEL_WARNING, msg, ##__VA_ARGS__);
#else
    #define WINDY_WARNING(msg, ...)
#endif

// logs info message if info logs are enabled, otherwise does nothing
#if LOG_INFO_ENABLED == 1
    #define WINDY_INFO(msg, ...) log_output(LOG_LEVEL_INFO, msg, ##__VA_ARGS__);
#else
    #define WINDY_INFO(msg, ...)
#endif

// logs debug message if debug logs are enabled, otherwise does nothing
#if LOG_DEBUG_ENABLED == 1
    #define WINDY_DEBUG(msg, ...) log_output(LOG_LEVEL_INFO, msg, ##__VA_ARGS__);
#else
    #define WINDY_DEBUG(msg, ...)
#endif

// logs trace message if trace logs are enabled, otherwise does nothing
#if LOG_TRACE_ENABLED == 1
    #define WINDY_TRACE(msg, ...) log_output(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__);
#else
    #define WINDY_TRACE(msg, ...)
#endif