#include "lib.h"

/**
 * @brief Structure to hold the working state for the Euler tour algorithm.
 *
 * This structure groups together all arrays and variables needed during
 * the execution of the Euler tour construction, reducing the number of
 * function arguments and improving code clarity.
 * @param used Array indicating whether each vertex is included in K (the Euler tour)
 * @param new_edge Array indicating whether each edge is unused (1: unused, 0: used)
 * @param used_list List of vertices for which used[v] == true (vertices to process)
 * @param used_list_size Current size of used_list
 * @param e_pos For each vertex v, the position in K where e(v) occurs, or -1 if undefined
 * @param n Number of vertices in the graph
 */

typedef struct s_euler_ctx
{
	int		*used;			// length n
	int		*new_edge;		// length |E|
	int		*used_list;		// list of vertices that used[v] is TRUE
	int		used_list_size;	// size of used_list
	int		*e_pos;			// position of vertices in K
	int		n;
}			t_euler_ctx;

/**
 * @brief Constructs a closed trail C starting at vertex v.
 *
 * This function follows the procedure TRACE as described in Hierholzer's algorithm,
 * using the context structure to manage state.
 *
 * this algorithm is guaranteed to halt on Eulerian graphs.
 *
 * @param vs Array of pointers to Vertex structures (the graph)
 * @param v  Starting vertex
 * @param ctx Pointer to the Euler context structure
 * @param C  Pointer to the pointer of the Node list representing the closed trail
 */

static void	trace(t_euler_ctx *ctx, Vertex **vs, int v,  Node **C)
{
	Edge	*edge;
	Node	*node;

	while (1)
	{
		edge = vs[v]->incidence;
		while (edge && !ctx->new_edge[edge->id])
			edge = edge->next;
		if (!edge) 								// all edges incident with v are used
			return ;
		ctx->new_edge[edge->id] = 0;
		node = create_node(edge->id);
		append_node(C, node); 					// append the node to the last of C
		if ((ctx->e_pos)[v] == -1)				// v is not in K yet ?
			(ctx->e_pos)[v] = node->edge_id; 	// wherever is fine
		v = edge->to;
		if (!ctx->used[v])
		{
			ctx->used[v] = 1;
			ctx->used_list[ctx->used_list_size++] = v;
		}
	}
}

/**
 * @brief Inserts the closed trail C into K at the position of insert_edge_id.
 *
 * @param K Pointer to the pointer of the Node list representing the Euler tour
 * @param C Pointer to the Node list representing the closed trail to insert
 * @param insert_edge_id The edge_id in K before which C should be inserted
 */

static void	insert_C_in_K(Node **K, Node *C, int insert_edge_id)
{
	Node	*cur;
	Node	*prev;
	Node	*last;

	if (!C)
		return ;
	cur = *K;
	while (cur && cur->edge_id != insert_edge_id)
		cur = cur->next;
	if (!cur)
	{
		append_node(K, C);
		return ;
	}
	prev = cur->prev;
	if (prev)
		prev->next = C;
	C->prev = prev;
	last = get_last_node(C);
	last->next = cur;
	cur->prev = last;
	if (cur == *K)
		*K = C;
}

/**
 * @brief Main function to construct the Euler tour using Hierholzer's algorithm.
 *
 * @param vs Array of pointers to Vertex structures (the graph)
 * @param n  Number of vertices
 * @param s  Starting vertex
 * @param K  Pointer to the pointer of the Node list representing the Euler tour
 */

void	algo_euler(Vertex **vs, int n, int s, Node **K)
{
	t_euler_ctx	ctx;
	int			i;
	Edge		*e;
	int			u;
	Node		*C;

	ctx.n = n;
    ctx.used = (int *)xcalloc(n, sizeof(int));
    ctx.new_edge = (int *)xcalloc(n * n, sizeof(int));
    ctx.used_list = (int *)xmalloc(sizeof(int) * n);
    ctx.used_list_size = 0;
    ctx.e_pos = (int *)xmalloc(sizeof(int) * n);
	i = 0;
	while (i < n)
		ctx.e_pos[i++] = -1;
	i = 0;
	while (i < n)
	{
		e = vs[i]->incidence;
		while (e)
		{
			ctx.new_edge[e->id] = 1; // set edges those are actually in G
			e = e->next;
		}
		i++;
	}
	ctx.used[s] = 1;
	ctx.used_list[ctx.used_list_size++] = s;
	trace(&ctx, vs, s, K);
	while (ctx.used_list_size > 0)
	{
		u = ctx.used_list[--ctx.used_list_size];
		C = NULL;
		trace(&ctx, vs, u,&C);
		insert_C_in_K(K, C, ctx.e_pos[u]);
	}
	xfree(ctx.used, sizeof(int) * n);
	xfree(ctx.new_edge, sizeof(int) * n * n);
	xfree(ctx.used_list, sizeof(int) * n);
	xfree(ctx.e_pos, sizeof(int) * n);
}
