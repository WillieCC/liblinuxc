#include <stdlib.h>
#include <string.h>
#include "safe_macro_io.h"

int main() {
    const char *filename = "example.txt";
    const char *data_to_write = "Hello World!";
    char data_read[50];

    int file_descriptor = safe_open_mode(filename, O_CREAT | O_WRONLY,0644);
    if (file_descriptor == -1) {
        exit(1);
    }

    ssize_t bytes_written = safe_write(file_descriptor, data_to_write, strlen(data_to_write));
    if (bytes_written == -1) {
        close(file_descriptor);
        exit(1);
    }

    safe_close(file_descriptor);


    file_descriptor = safe_open(filename, O_RDONLY);
    if (file_descriptor == -1) {
        exit(1);
    }

    ssize_t bytes_read = safe_read(file_descriptor, data_read, sizeof(data_read));
    if (bytes_read == -1) {
        close(file_descriptor);
        exit(1);
    }


    safe_close(file_descriptor);

    data_read[bytes_read] = '\0';
    printf("Read from file: %s\n", data_read);
    return 0;
}

