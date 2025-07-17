CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../include
LDFLAGS = -lm
TARGET = knight

MAIN_SRC = main.c
MAIN_OBJ = main.o

LIB_SRCS = $(filter-out $(MAIN_SRC), $(wildcard *.c))
LIB_OBJS = $(LIB_SRCS:.c=.o)

DISTDIR = ../dist
BASE_LIB = $(DISTDIR)/lib.a
THIS_LIB = $(DISTDIR)/lib$(TARGET).a
OTHER_LIBS = $(filter-out $(BASE_LIB) $(THIS_LIB), $(wildcard $(DISTDIR)/*.a))

all: $(TARGET)

$(TARGET): $(MAIN_OBJ)
	$(CC) -o $@ $(MAIN_OBJ) $(THIS_LIB) $(OTHER_LIBS) $(BASE_LIB) $(LDFLAGS)

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

archive: $(LIB_OBJS)
	@mkdir -p $(DISTDIR)
	@if [ -n "$(LIB_OBJS)" ]; then \
		ar rcs $(DISTDIR)/lib$(TARGET).a $(LIB_OBJS); \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJ) $(LIB_OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all archive clean fclean re
