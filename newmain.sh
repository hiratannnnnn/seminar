#!/bin/bash
# filepath: c:\Users\PC_User\seminar\newmain.sh

show_usage() {
	echo "Usage:"
	echo "  $0 <dirname>					# Create project in current directory"
	echo "  $0 <path/dirname>			  # Create project with path"
	echo "  $0 <dirname> <subdir>		  # Create project in subdir/dirname"
	echo ""
	echo "Examples:"
	echo "  $0 myproj					  # Creates ./myproj/"
	echo "  $0 Jungnickel/myproj		  # Creates ./Jungnickel/myproj/"
	echo "  $0 myproj algorithms		  # Creates ./algorithms/myproj/"
}

if [ $# -eq 0 ] || [ $# -gt 2 ]; then
	show_usage
	exit 1
fi

# 引数の解析
if [ $# -eq 1 ]; then
	# Case 1: dirname または path/dirname
	FULL_PATH="$1"
	if [[ "$FULL_PATH" == *"/"* ]]; then
		# path/dirname 形式
		PARENT_DIR=$(dirname "$FULL_PATH")
		DIR=$(basename "$FULL_PATH")
	else
		# dirname のみ
		PARENT_DIR="."
		DIR="$FULL_PATH"
	fi
elif [ $# -eq 2 ]; then
	# Case 2: dirname subdir
	DIR="$1"
	PARENT_DIR="$2"
	FULL_PATH="$PARENT_DIR/$DIR"
fi

DIR_UPPER=$(echo "$DIR" | tr '[:lower:]' '[:upper:]')

# ディレクトリ存在チェック
if [ -d "$FULL_PATH" ]; then
	echo "Error: Directory $FULL_PATH already exists. Aborting to prevent overwrite."
	exit 1
fi

# 親ディレクトリ作成（必要に応じて）
mkdir -p "$PARENT_DIR"
mkdir "$FULL_PATH"

# 相対パスの計算（include/ と dist/ への）
# PARENT_DIR から seminar/ への相対パス
if [ "$PARENT_DIR" = "." ]; then
	REL_TO_ROOT="."
	INCLUDE_PATH="../include"
	DIST_PATH="../dist"
else
	# パスの深さを計算
	DEPTH=$(echo "$PARENT_DIR" | tr -cd '/' | wc -c)
	REL_TO_ROOT=""
	for ((i=0; i<=DEPTH; i++)); do
		if [ $i -eq 0 ]; then
			REL_TO_ROOT=".."
		else
			REL_TO_ROOT="../$REL_TO_ROOT"
		fi
	done
	INCLUDE_PATH="$REL_TO_ROOT/include"
	DIST_PATH="$REL_TO_ROOT/dist"
fi

# ヘッダーファイル作成（親ディレクトリにincludeがある場合）
if [ -d "$PARENT_DIR/include" ]; then
	HEADER_DIR="$PARENT_DIR/include"
	HEADER_INCLUDE="../include"
else
	# seminar/include に作成
	HEADER_DIR="include"
	HEADER_INCLUDE="$INCLUDE_PATH"
fi

mkdir -p "$HEADER_DIR"

cat > "$HEADER_DIR/${DIR}.h" << EOF
#ifndef ${DIR_UPPER}_H
# define ${DIR_UPPER}_H

# include "$INCLUDE_PATH/lib.h"

#endif
EOF

# Makefile作成
cat > "$FULL_PATH/Makefile" << EOF
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$HEADER_INCLUDE -I$INCLUDE_PATH
LDFLAGS = -L$DIST_PATH -lpath -lmintree -lm
TARGET = $DIR

MAIN_SRCS = \$(wildcard main*.c)
MAIN_OBJS = \$(MAIN_SRCS:.c=.o)

LIB_SRCS = \$(filter-out \$(MAIN_SRCS), \$(wildcard *.c))
LIB_OBJS = \$(LIB_SRCS:.c=.o)

DISTDIR = $DIST_PATH
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
	rm -f \$(THIS_LIB)

re: fclean all

.PHONY: all ar clean fclean re
EOF

# main.c作成
cat > "$FULL_PATH/main.c" << EOF
// filepath: \$(pwd)/$FULL_PATH/main.c
#include "$HEADER_INCLUDE/${DIR}.h"

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
echo "  - $HEADER_DIR/${DIR}.h"
echo "  - $FULL_PATH/Makefile"
echo "  - $FULL_PATH/main.c"
echo ""
echo "To build the project:"
echo "  cd $FULL_PATH"
echo "  make"
