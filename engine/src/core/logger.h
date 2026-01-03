#pragma once
#include "defines.h"

#define LOG_WARNING_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace log for release
#if WRELEASE == 1
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

WAPI void log_output(log_level lvl, const char* msg, ...);

// logs fatal message
#ifndef WFATAL
    #define WFATAL(msg, ...) log_output(LOG_LEVEL_FATAL, msg, ##__VA_ARGS__);
#endif

// logs error message
#ifndef WERROR
    #define WERROR(msg, ...) log_output(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__);
#endif

// logs warning message if warning logs are enabled, otherwise does nothing
#if LOG_WARNING_ENABLED == 1
    #define WWARNING(msg, ...) log_output(LOG_LEVEL_WARNING, msg, ##__VA_ARGS__);
#else
    #define WWARNING(msg, ...)
#endif

// logs info message if info logs are enabled, otherwise does nothing
#if LOG_INFO_ENABLED == 1
    #define WINFO(msg, ...) log_output(LOG_LEVEL_INFO, msg, ##__VA_ARGS__);
#else
    #define WINFO(msg, ...)
#endif

// logs debug message if debug logs are enabled, otherwise does nothing
#if LOG_DEBUG_ENABLED == 1
    #define WDEBUG(msg, ...) log_output(LOG_LEVEL_INFO, msg, ##__VA_ARGS__);
#else
    #define WDEBUG(msg, ...)
#endif

// logs trace message if trace logs are enabled, otherwise does nothing
#if LOG_TRACE_ENABLED == 1
    #define WTRACE(msg, ...) log_output(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__);
#else
    #define WTRACE(msg, ...)
#endif