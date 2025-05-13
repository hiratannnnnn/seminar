CC = gcc
CFLAGS = -Wall -O2
LDFLAGS = -lm
TARGET = jung
SRCS = main.c count_degrees.c generate_matrix.c generate_prufer_code.c is_tree.c print_graph.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c jung.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

delres:
	rm -rf result_*

re: fclean all

.PHONY: all clean fclean re delres