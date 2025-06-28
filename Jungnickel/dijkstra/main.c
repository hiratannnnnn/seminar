// filepath: /Users/tomoyahirata/Documents/seminar/Jungnickel/dijkstra/main.c
#include "dijkstra.h"

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
