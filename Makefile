IO_OBJS = test_io.o
TIME_OBJS = test_time.o

CFLAGS = -Wall -Wextra -O3
 
default:all
all: test_io test_time
 
test_io: $(IO_OBJS)
	$(CC) -o $@ $^

test_time: $(TIME_OBJS)
	$(CC) -o $@ $^

clean:
	rm -vrf *.o test_io test_time
