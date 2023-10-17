#ifndef _SAFE_MACRO_IO_H
#define _SAFE_MACRO_IO_H
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

static inline ssize_t safe_open(const char *pathname,int32_t flags)
{
    int32_t fd=0;
    while(1)
    {
        fd = open(pathname, flags);
        if (fd != -1) 
        {
            //printf("Open fd: %d\n",fd); //Debug
            break;
        }
        
        if (errno != EINTR) {
            perror(pathname);
            break;
        } 
    }

    return fd;
}


static inline ssize_t safe_open_mode(const char *pathname,int32_t flags,int32_t mode)
{
    int32_t fd=0;
    while(1)
    {
        fd = open(pathname, flags, mode);
        if (fd != -1) 
        {
            //printf("Open fd: %d\n",fd); //Debug
            break;
        }
        
        if (errno != EINTR) {
            perror(pathname);
            break;
        } 
    }

    return fd;
}

static inline ssize_t safe_write(int32_t fd,const void* buf,size_t count)
{
    ssize_t ret;
    while (1) { 
        ret = write(fd, buf, count);
        if (ret != -1) {
            break; 
        }
        
        if (errno != EINTR) { 
            fprintf(stderr, "Failed to write fd: %d", fd);
            break;
        }
    }
        
    return ret;
}

static inline ssize_t safe_read(int32_t fd,void* buf,size_t count)
{
    ssize_t ret;
    while (1) { 
        ret = read(fd, buf, count);
        if (ret != -1) {
            break; 
        }
        
        if (errno != EINTR) { 
            fprintf(stderr, "Failed to write fd: %d", fd);
            break;
        }
    }
        
    return ret;

}

static inline int32_t safe_close(int32_t fd)
{
    int32_t ret;

    while(1) {
        ret = close(fd);
        if(ret != -1){
            break;
        }
            
        if (errno != EINTR || errno !=EBADF ) {
            fprintf(stderr, "Failed to close fd: %d", fd);
            break;
        }
    }

    return ret;
}

#endif
