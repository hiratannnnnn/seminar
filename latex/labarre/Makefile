CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes -I../../include
TARGET = labarre

SRCDIR = srcs
OBJDIR = objs

DISTDIR = ../../dist
# Link against existing libraries in ../../dist
LIBS = $(DISTDIR)/libperms.a \
       $(DISTDIR)/libpath.a \
       $(DISTDIR)/libmintree.a \
       $(DISTDIR)/lib.a

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS) -lm

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(TARGET) $(TARGET).exe

re: fclean all

.PHONY: all clean fclean re
