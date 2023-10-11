
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

#define SAFE_MEMCPY(dest, src, size) \
    do { \
        if ((size) > 0) { \
            memcpy(dest, src, size); \
        } \
    } while (0)

#define SAFE_STRNCPY(dest, src, dest_size) \
    do { \
        if (dest_size > 0) { \
            strncpy(dest, src, dest_size - 1); \
            dest[dest_size - 1] = '\0'; \
        } \
    } while (0)


#define SAFE_SNPRINTF(str, size, format, ...) \
    do { \
        memset(str, 0, size); \
        int ret; \
        va_list args; \
        va_start(args, format); \
        ret = vsnprintf(str, size, format, args); \
        va_end(args); \
        if (ret < 0) { \
            str[0] = '\0'; \
            ret = 0; \
        } \
    } while (0)

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


#define SAFE_SELECT(nfds, readfds, writefds, exceptfds, timeout) \
    ({ \
        int ret; \
        while (1) { \
            ret = select(nfds, readfds, writefds, exceptfds, timeout); \
            if (ret != -1) { \
                break; \
            } \
            if (errno != EINTR) { \
                break; \
            } \
        } \
        ret; \
    })

#define SAFE_CONNECT(sockfd, addr, addrlen) \
    ({ \
        int ret; \
        while (1) { \
            ret = connect(sockfd, addr, addrlen); \
            if (ret != -1) { \
                break; \
            } \
            if (errno != EINTR || errno != EINPROGRESS) { \
                break; \
            } \
        } \
        ret; \
    })

#define SAFE_ACCEPT(sockfd, addr, addrlen) \
    ({ \
        int ret; \
        while (1) { \
            ret = accept(sockfd, addr, addrlen); \
            if (ret != -1) { \
                break; \
            } \
            if (errno != EINTR) { \
                break; \
            } \
        } \
        ret; \
    })

#define SAFE_SEND(sockfd, buf, len, flags) \
    ({ \
        ssize_t ret; \
        while (1) { \
            ret = send(sockfd, buf, len, flags); \
            if (ret != -1) { \
                break; \
            } \
            if (errno != EINTR) { \
                break; \
            } \
        } \
        ret; \
    })

#define SAFE_RECV(fd, buf, len, flags) \
    ({ \
        ssize_t ret; \
        while (1) { \
            ret = recv(fd, buf, len, flags); \
            if (ret != -1) { \
                break; \
            } \
            if (errno != EINTR) { \
                break; \
            } \
        } \
        ret; \
    })

#define SAFE_SENDTO(fd, buf, len, flags, dest_addr, addrlen) \
    ({ \
        ssize_t ret; \
        while (1) { \
            ret = sendto(fd, buf, len, flags, dest_addr, addrlen); \
            if (ret != -1) { \
                break; \
            } \
            if (errno != EINTR) { \
                break; \
            } \
        } \
        ret; \
    })

#define SAFE_RECVFROM(fd, buf, len, flags, src_addr, addrlen) \
    ({ \
        ssize_t ret; \
        while (1) { \
            ret = recvfrom(fd, buf, len, flags, src_addr, addrlen); \
            if (ret != -1) { \
                break; \
            } \
            if (errno != EINTR) { \
                break; \
            } \
        } \
        ret; \
    })

