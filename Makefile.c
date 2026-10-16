/*Author:Csd4376*/


CC = gcc
CFLAGS = -Wall -O2

all: test_scheduling

test_scheduling: test_scheduling.c
	$(CC) $(CFLAGS) -o test_scheduling test_scheduling.c

clean:
	rm -f test_scheduling *.o
