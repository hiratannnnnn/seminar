CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./include -I../include
LDFLAGS = -L../dist -lpath -lmintree -lm
TARGET = genome

SRCDIR = srcs
OBJDIR = objs

MAIN_SRCS = $(wildcard main*.c)
LIB_SRCS = $(filter-out $(MAIN_SRCS), $(wildcard $(SRCDIR)/*.c))

MAIN_OBJS = $(MAIN_SRCS:%.c=$(OBJDIR)/%.o)
LIB_OBJS = $(LIB_SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

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
		if [ -f $(THIS_LIB) ]; then \
			$(CC) -o $$exec $$obj $(THIS_LIB) $(OTHER_LIBS) $(BASE_LIB) $(LDFLAGS); \
		else \
			$(CC) -o $$exec $$obj $(OTHER_LIBS) $(BASE_LIB) $(LDFLAGS); \
		fi; \
	done

ar: $(LIB_OBJS)
	@mkdir -p $(DISTDIR)
	@if [ -n "$(LIB_OBJS)" ]; then \
		ar rcs $(DISTDIR)/lib$(TARGET).a $(LIB_OBJS); \
		echo "Archive created: $(THIS_LIB)"; \
	fi

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_OBJS) $(LIB_OBJS)

fclean: clean
	rm -f $(TARGET)*
	rm -f $(THIS_LIB)

re: fclean all

.PHONY: all ar clean fclean re
