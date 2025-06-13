// filepath: /c/Users/PC_User/seminar/Jungnickel/knight/main.c
#include "knight.h"

int main(void)
{
	// Test (3, 5)
	printf("Testing (3, 5):\n");
	proc_start = clock();
	solve_knight(3, 5);
	proc_end = clock();
	print_info();
	
	printf("\nTesting (5, 3):\n");
	proc_start = clock();
	solve_knight(5, 3);
	proc_end = clock();
	print_info();
	
	return (0);
}
