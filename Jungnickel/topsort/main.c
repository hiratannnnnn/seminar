// (a) adjacency lists A1,...,An;
// (b) a function ind, where ind(v) = din(v);
// (c) a function topnr, where topnr(v) gives the index of vertex v in the topological sorting;
// (d) a list L of the vertices v having ind(v) = 0;
// (e) a Boolean variable acyclic and an integer variable N (for counting).

#include "topsort.h"

int		main(void)
{
	int 	n;
	int 	**matrix;
	Vertex	**vs;
	int		*topnr;

	n = 12;
	save_random_digraph(n, 0.7, "test_graph.txt");

	matrix = read_adj(&n, "test_graph.txt");
	vs = adj_matrix_to_vertices(matrix, n, 0); // directed = 0
	print_vertices(vs, n);

	topnr = calloc(n, sizeof(int));
	if (topnr)
	{
		
	}
	free_array_int(matrix, n);
	free_vertex_array(vs, n);
	return (0);
}
// typedef struct Vertex
// {
//     int         id;
//     Edge        *incidence;
// }               Vertex;
// typedef struct Edge
// {
//     int         id;
//     int         from;
//     int         to;
//     int         used;
//     struct Edge *next;
// }               Edge;
