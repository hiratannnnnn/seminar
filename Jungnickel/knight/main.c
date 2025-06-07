// filepath: /c/Users/PC_User/seminar/Jungnickel/knight/main.c
#include "knight.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
	proc_start = clock();

	// solve_knight(3, 10);
	// solve_knight(3, 12);
	// solve_knight(5, 6);
	// solve_knight(5, 8);
	// solve_knight(6, 6);
	// solve_knight(6, 7);
	solve_knight(6, 8); // insanely takes time... Idk why
	// solve_knight(7, 8);
	// solve_knight(8, 8);

	proc_end = clock();
	print_info();
	return (0);
}
