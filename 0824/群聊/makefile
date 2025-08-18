CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -pthread


SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
EXES = $(SRCS:.c=)

all: $(EXES)

$(EXES): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $@.o -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJS) $(EXES)
