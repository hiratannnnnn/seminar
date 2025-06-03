// filepath: /c/Users/PC_User/seminar/Jungnickel/test/main.c
#include "test.h"

size_t		mem = 0;
size_t		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	srand((unsigned int)time(NULL));
	proc_start = clock();

	int *arr;
	int n;

	n = 12;
	arr = random_perm(n);
	if (!arr)
		return (1);
	print_array_int(arr, n);
	printf("max: %d\n", max_of_array(arr, n));
	printf("min: %d\n", min_of_array(arr, n));
	free_array_int(arr, n);
	proc_end = clock();
	print_info();
	return (0);
}
