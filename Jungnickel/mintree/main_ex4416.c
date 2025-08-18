// filepath: /c/Users/PC_User/seminar/Jungnickel/mintree/main.c
#include "mintree.h"

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
	Vertex **vs;
	int n;

	matrix = read_adj(&n, "ex4416.txt");
	print_matrix_int(matrix, n, n);
	vs = adj_matrix_to_vertices(matrix, n, 0);
	// print_vertices(vs, n, 0);
	printf("0: L  (London)\n");
	printf("1: MC (Mexico City)\n");
	printf("2: NY (New York)\n");
	printf("3: Pa (Paris)\n");
	printf("4: Pe (Peking, Beijing)\n");
	printf("5: To (Tokyo)\n");

	printf("\n---------------------------\nConducting PRIM for Ex. 4.4.16\n\n");
	proc_start = clock();
	solve_prim(vs, 0, n, 0);
	reset_labels(vs, n);	print_info();//	sleep(3);

	printf("\n---------------------------\nConducting KRUSKAL for Ex. 4.4.16\n\n");
	proc_start = clock();
	solve_kruskal(vs, n, 0);
	reset_labels(vs, n);	print_info();//	sleep(3);

	printf("\n---------------------------\nConducting BORUVKA for Ex. 4.4.16\n\n");
	proc_start = clock();
	solve_boruvka(vs, n, 0);
	reset_labels(vs, n);	print_info();

	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
	print_info();
	return (0);
}
