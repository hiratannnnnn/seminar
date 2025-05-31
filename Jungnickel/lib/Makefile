CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../include
AR = ar
ARFLAGS = rcs
LIB = lib.a

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: $(LIB)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB)

re:	fclean all
