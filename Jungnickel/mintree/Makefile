CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../include
LDFLAGS = -lm
TARGET = mintree

MAIN_SRCS = $(wildcard main*.c)
MAIN_OBJS = $(MAIN_SRCS:.c=.o)

LIB_SRCS = $(filter-out $(MAIN_SRCS), $(wildcard *.c))
LIB_OBJS = $(LIB_SRCS:.c=.o)

DISTDIR = ../dist
BASE_LIB = $(DISTDIR)/lib.a
THIS_LIB = $(DISTDIR)/lib$(TARGET).a
OTHER_LIBS = $(filter-out $(BASE_LIB) $(THIS_LIB), $(wildcard $(DISTDIR)/*.a))

all: ar $(MAIN_OBJS)
	@for obj in $(MAIN_OBJS); do \
		base=$$(basename $$obj .o); \
		suffix=$$(echo $$base | sed 's/^main//'); \
		exec=$(TARGET)$$suffix; \
		echo "Building executable: $$exec"; \
		$(CC) -o $$exec $$obj $(THIS_LIB) $(OTHER_LIBS) $(BASE_LIB) $(LDFLAGS); \
	done

ar: $(LIB_OBJS)
	@mkdir -p $(DISTDIR)
	@if [ -n "$(LIB_OBJS)" ]; then \
		ar rcs $(DISTDIR)/lib$(TARGET).a $(LIB_OBJS); \
		echo "Archive created: $(THIS_LIB)"; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJ) $(LIB_OBJS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all archive clean fclean re
