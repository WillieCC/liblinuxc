#ifndef _SAFE_MACRO_TIME_H
#define _SAFE_MACRO_TIME_H
#include <time.h>
#include <assert.h>
#include <errno.h>

#define SAFE_MSLEEP(msec) \
    do { \
        struct timespec timeout; \
        int rc; \
        \
        timeout.tv_sec = (msec) / 1000; \
        timeout.tv_nsec = ((msec) % 1000) * 1000 * 1000; \
        \
        do { \
            rc = nanosleep(&timeout, &timeout); \
        } while (rc == -1 && errno == EINTR); \
        \
        assert(rc == 0); \
    } while (0)

#define SAFE_USLEEP(usec) \
    do { \
        struct timespec timeout; \
        timeout.tv_sec = (usec) / 1000000; \
        timeout.tv_nsec = ((usec) % 1000000) * 1000; \
        int rc; \
        \
        do { \
            rc = nanosleep(&timeout, &timeout); \
        } while (rc == -1 && errno == EINTR); \
        \
        assert(rc == 0); \
    } while (0)

#endif
