CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../include
AR = ar
ARFLAGS = rcs
#LIB = lib.a
TARGET = lib
DISTDIR = ../dist

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
LIB = $(DISTDIR)/$(TARGET).a

all: ar

ar: $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(DISTDIR)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Archive created: $@"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB)

re:	fclean all
