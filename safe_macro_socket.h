

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

