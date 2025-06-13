CC = gcc
CFLAGS = -Iinclude
SRCS = $(wildcard srcs/*.c) globals.c
TARGET = report2 report5

all: $(TARGET)

report2: main_2.c $(SRCS)
	$(CC) $(CFLAGS) -o $@ main_2.c $(SRCS)

report5: main_5.c $(SRCS)
	$(CC) $(CFLAGS) -o $@ main_5.c $(SRCS)

clean:
	rm -f $(TARGET)

fclean:	clean

re: fclean all

.PHONY: all clean fclean re
