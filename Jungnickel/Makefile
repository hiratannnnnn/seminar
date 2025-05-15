CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
LDFLAGS = -lm
TARGET = jung
LIB = libjung.a
SRCS = main.c
OBJS = $(SRCS:.c=.o)
LIBSRCS = is_tree.c generate_adj.c utils.c utils_free.c
LIBOBJS = $(LIBSRCS:.c=.o)

all: $(LIB) $(TARGET)

$(LIB): $(LIBOBJS)
	$(AR) rcs $@ $^

$(TARGET): $(OBJS) $(LIB)
	$(CC) -o $@ $(OBJS) $(LIB) $(LDFLAGS)

%.o: %.c jung.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(LIBOBJS)

fclean: clean
	rm -f $(TARGET)
	rm -f $(LIB)

delres:
	rm -rf result_*
	rm -rf results_*
	rm -f *.out
	rm -f *.exe

re: fclean all

.PHONY: all clean fclean re delres
