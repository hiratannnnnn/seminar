// (a) adjacency lists A1,...,An;
// (b) a function ind, where ind(v) = din(v);
// (c) a function topnr, where topnr(v) gives the index of vertex v in the topological sorting;
// (d) a list L of the vertices v having ind(v) = 0;
// (e) a Boolean variable acyclic and an integer variable N (for counting).

#include "topsort.h"

size_t 		mem = 0;
size_t 		mem_peak = 0;
clock_t		proc_start;
clock_t		proc_end;

int		main(void)
{
	proc_start = clock();
	int 	n;
	int 	**matrix;
	Vertex	**vs;
	int		*topnr;

	n = 30;
	srand(time(NULL) + clock());
	save_some_matrix(n, 0.1, generate_random_DAG, "test_graph.txt");

	matrix = read_adj(&n, "test_graph.txt");
	vs = adj_matrix_to_vertices(matrix, n, 0); // directed = 0
	print_vertices(vs, n);

	topnr = xcalloc(n, sizeof(int));
	if (!topnr)
	{
		free_matrix_int(matrix, n, n);
		free_vertex_array(vs, n);
		return (1);
	}
	printf("%d\n", topsort(vs, n, topnr));
	print_array_int(topnr, n);

	// free
	free_matrix_int(matrix, n, n);
	free_vertex_array(vs, n);
	xfree(topnr, sizeof(int) * n);

	proc_end = clock();
    print_info();

	return (0);
}
