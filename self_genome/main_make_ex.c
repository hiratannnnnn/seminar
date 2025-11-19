// filepath: $(pwd)/genome/main.c
#include "genome.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	// for generating some permutation.
	// make_example(6, "tests/ex_6.txt", 0.1);
	// make_example(20, "tests/ex_20.txt", 0.1);
	// make_example(100, "tests/ex_100.txt", 0.1);
	// make_example(1000, "tests/ex_1000.txt", 0.1);
	// make_example(10000, "tests/ex_10000.txt", 0.1);

	print_info();
	return (0);
}
