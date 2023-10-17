#ifndef _SAFE_MACRO_STRING_H
#define _SAFE_MACRO_STRING_H
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

static inline void safe_strncpy(char *dest, const char *src, size_t dest_size) {
    if (dest_size > 0) {
        strncpy(dest, src, dest_size - 1);
        dest[dest_size - 1] = '\0';
    }
}

static inline void safe_snprintf(char *str, size_t size, const char *format, ...) {
    memset(str, 0, size);
    va_list args;
    va_start(args, format);
    int ret = vsnprintf(str, size, format, args);
    va_end(args);
    if (ret < 0) {
        str[0] = '\0';
        ret = 0;
    }
}

#endif    
