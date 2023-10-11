
#define SAFE_OPEN(pathname, flags) \
    ({ \
        int fd; \
        while (1) { \
            fd = open(pathname, flags); \
            if (fd != -1) { \
                break; \
            } \
            if (fd != EINTR) { \
                perror(pathname); \
                break; \
            } \
        } \
        fd; \
    })


#define SAFE_WRITE(fd, buf, count) \
    ({ \
        ssize_t ret; \
        while (1) { \
            ret = write(fd, buf, count); \
            if (ret != -1) { \
                break; \
            } \
            if (errno != EINTR) { \
               fprintf(stderr, "Failed to write fd: %d\n", fd); \
               break; \
            } \
        } \
        ret; \
    })

#define SAFE_READ(fd, buf, count) \
    ({ \
        ssize_t ret; \
        while (1) { \
            ret = read(fd, buf, count); \
            if (ret != -1) { \
                break; \
            } \
            if (errno != EINTR) { \
                fprintf(stderr, "Failed to read fd: %d\n", fd); \
                break; \
            } \
        } \
        ret; \
    })

#define SAFE_CLOSE(fd) \
    do { \
        if ((fd) > 0) { \
            while (close(fd) == -1) { \
                if (errno != EINTR || errno != EINPROGRESS) { \
                    fprintf(stderr, "Failed to close fd: %d\n", fd); \
                    return -1; \
                } \
            } \
        } \
    } while (0)

