#!/bin/bash
# filepath: c:\Users\PC_User\seminar\Jungnickel\newmain.sh

if [ $# -ne 1 ]; then
	echo "Usage: $0 <dirname>"
	exit 1
fi

DIR="$1"
DIR_UPPER=$(echo "$DIR" | tr '[:lower:]' '[:upper:]')

if [ -d "$DIR" ]; then
	echo "Error: Directory $DIR already exists. Aborting to prevent overwrite."
	exit 1
fi

mkdir "$DIR"

cat > "include/${DIR}.h" << EOF
#ifndef ${DIR_UPPER}_H
# define ${DIR_UPPER}_H

# include "lib.h"

#endif
EOF

cat > "$DIR/Makefile" << EOF
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I../include
LDFLAGS = -lm
TARGET = $DIR

MAIN_SRCS = \$(wildcard main*.c)
MAIN_OBJS = \$(MAIN_SRCS:.c=.o)

LIB_SRCS = \$(filter-out \$(MAIN_SRCS), \$(wildcard *.c))
LIB_OBJS = \$(LIB_SRCS:.c=.o)

DISTDIR = ../dist
BASE_LIB = \$(DISTDIR)/lib.a
THIS_LIB = \$(DISTDIR)/lib\$(TARGET).a
OTHER_LIBS = \$(filter-out \$(BASE_LIB) \$(THIS_LIB), \$(wildcard \$(DISTDIR)/*.a))

all: ar \$(MAIN_OBJS)
	@for obj in \$(MAIN_OBJS); do \\
		base=\$\$(basename \$\$obj .o); \\
		suffix=\$\$(echo \$\$base | sed 's/^main//'); \\
		exec=\$(TARGET)\$\$suffix; \\
		echo "Building executable: \$\$exec"; \\
		\$(CC) -o \$\$exec \$\$obj \$(THIS_LIB) \$(OTHER_LIBS) \$(BASE_LIB) \$(LDFLAGS); \\
	done

ar: \$(LIB_OBJS)
	@mkdir -p \$(DISTDIR)
	@if [ -n "\$(LIB_OBJS)" ]; then \\
		ar rcs \$(DISTDIR)/lib\$(TARGET).a \$(LIB_OBJS); \\
		echo "Archive created: \$(THIS_LIB)"; \\
	fi

%.o: %.c
	\$(CC) \$(CFLAGS) -c \$< -o \$@

clean:
	rm -f \$(MAIN_OBJS) \$(LIB_OBJS)

fclean: clean
	rm -f \$(TARGET)*

re: fclean all

.PHONY: all ar clean fclean re
EOF

cat > "$DIR/main.c" << EOF
// filepath: \$(pwd)/$DIR/main.c
#include "${DIR}.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	int **matrix;
	int n;


	// free

	print_info();
	return (0);
}
EOF

echo "Project structure created for: $DIR"
echo "Created files:"
echo "  - include/${DIR}.h"
echo "  - $DIR/Makefile"
echo "  - $DIR/main.c"
