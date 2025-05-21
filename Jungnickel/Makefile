CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2
LDFLAGS = -lm
TARGET = jung
LIB = libjung.a
SRCS = main.c algo_EULER.c
OBJS = $(SRCS:.c=.o)
LIBSRCS = lib/graph_analysis.c \
lib/graph_connections.c \
lib/graph_conversion.c \
lib/matrix_operations.c \
lib/path_operations.c \
lib/random_euler.c \
lib/random_graph.c \
lib/random_tree.c \
lib/read_adj.c \
lib/utils_basic.c \
lib/utils_print.c \
lib/utils_free.c \
lib/utils_edges.c \
lib/utils_euler.c \
lib/utils_lists.c
LIBOBJS = $(LIBSRCS:.c=.o)

all: $(LIB) $(TARGET)

$(LIB): $(LIBOBJS)
	$(AR) rcs $@ $^

$(TARGET): $(OBJS) $(LIB)
	$(CC) -o $@ $(OBJS) $(LIB) $(LDFLAGS)

%.o: %.c jung.h
	$(CC) -c $< -o $@ $(CFLAGS)

lib/%.o: lib/%.c jung.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS) $(LIBOBJS)

fclean: clean delres
	rm -f $(TARGET)
	rm -f $(LIB)

delres:
	rm -rf result_*
	rm -rf results_*
	rm -f *.out
	rm -f *.exe
	rm -f *_graph.txt
	rm -f *_path.txt

re: fclean all

.PHONY: all clean fclean re delres
