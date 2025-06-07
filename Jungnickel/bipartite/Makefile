CC = gcc
CFLAGS = -I../include
LDFLAGS = -lm
TARGET = bipartite
SRCS = main.c random_bigraph.c kuhn.c hungarian.c random_bigraph_cost.c
OBJS = $(SRCS:.c=.o)
LIBDIR = ../lib
LIB = $(LIBDIR)/lib.a

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	$(CC) -o $@ $(OBJS) $(LIB) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	$(MAKE) -C $(LIBDIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
