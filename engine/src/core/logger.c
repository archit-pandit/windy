#include "logger.h"
#include "asserts.h"
#include "platform/platform.h"

// TODO: remove (temp)
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 init_logging() {
    // TODO: create log file
    return TRUE;
}

void close_logging() {
    // TODO: clean logging/write queued entries
}

void log_output(log_level lvl, const char* msg, ...) {
    const char* lvl_strs[6] = {"[FATAL] ", "[ERROR] ", "[WARNING] ", "[INFO] ", "[DEBUG] ", "[TRACE] "};
    b8 is_err = lvl < LOG_LEVEL_WARNING;

    // BAD PRACTICE, imposing 32k limit on log entry
    const i32 msg_len = 32000;
    char out_msg[msg_len];
    memset(out_msg, 0, sizeof(out_msg));

    // format original message
    // NOTE: MS headers override GCC/clang va_list type with "typedef char* va_list" for some cases,
    // and will throw an error here. A workaround is to use __builtin_va_list
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, msg);
    vsnprintf(out_msg, 32000, msg, arg_ptr);
    va_end(arg_ptr);

    char out_msg2[32000];
    sprintf(out_msg2, "%s%s\n", lvl_strs[lvl], out_msg);
    
    // Platform specific output
    if (is_err) {
        platform_console_write_error(out_msg2, lvl);
    } else {
        platform_console_write(out_msg2, lvl);
    }
}

void report_assert_failure(const char* exp, const char* msg, const char* file, i32 line) {
    log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", exp, msg, file, line);
}