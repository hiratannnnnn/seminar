#!/bin/bash
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
SRCS = main.c
OBJS = \$(SRCS:.c=.o)
LIBDIR = ../lib
LIB = \$(LIBDIR)/lib.a

all: \$(TARGET)

\$(TARGET): \$(OBJS) \$(LIB)
	\$(CC) -o \$@ \$(OBJS) \$(LIB) \$(LDFLAGS)

%.o: %.c
	\$(CC) \$(CFLAGS) -c \$< -o \$@

\$(LIB):
	\$(MAKE) -C \$(LIBDIR)

clean:
	rm -f \$(OBJS)

fclean: clean
	rm -f \$(TARGET)

re: fclean all

.PHONY: all clean fclean re
EOF


cat > "$DIR/main.c" << EOF
// filepath: $(pwd)/$DIR/main.c
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

	proc_end = clock();
	print_info();
	return (0);
}
EOF
