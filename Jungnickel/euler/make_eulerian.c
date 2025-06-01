#include "euler.h"

static int     need_double_edge(int *degree, int n)
{
    int i;
    if (n % 2 == 1)
        return (0);
    for (i = 0; i < n; i++)
    {
        if (degree[i] == n - 1)
			return (1);
    }
	return (0);
}

typedef struct Euler_ctx
{
    Vertex  **vs;
	int 	*degree;
    int     *visited;
    int 	start;
    PathNode *head;
}				Euler_ctx;

static void free_ctx(Euler_ctx *ctx, int n)
{
	if (ctx->degree)
	{
		free_array_int(ctx->degree, n);
		ctx->degree = NULL;
	}
	if (ctx->visited)
	{
		free_array_int(ctx->visited, n);
		ctx->visited = NULL;
	}
	if (ctx->vs)
	{
		free_vertex_array(ctx->vs, n);
		ctx->vs = NULL;
	}
}

static int	backtrack_euler(Euler_ctx *ctx, int cur)
{
    Vertex      *v;
    Edge        *edge;
    PathNode    *node;
    int         length;

    v       = ctx->vs[cur];
    edge    = v->incidence;
    node    = create_pathnode(v);
    append_pathnode(&ctx->head, node);
	// print_path_node(ctx->head);
    length  = pathnode_length(ctx->head);
	// printf("[DEBUG] length: %d\n", length);
	// printf("[DEBUG] degree: %d\n", ctx->degree[cur]);


	if (length > 1 && ctx->degree[cur] % 2 == 1)
	{
		return 1;
	}

    while (edge)
    {
        if (!ctx->visited[edge->to])
        {
			ctx->visited[edge->to] = 1;
			// printf("[DEBUG] Moving to %d\n", edge->to);
			if (backtrack_euler(ctx, edge->to))
				return (1);
			ctx->visited[edge->to] = 0;
			// printf("[DEBUG] Returning to %d\n", edge->from);
			pathnode_pop_last(&ctx->head);
        }
        edge = edge->next;
    }
	return (0);
}

static void	delete_edge(Edge **edge_list, int to)
{
	Edge *prev, *cur, *tmp;

	prev = NULL;
	cur = *edge_list;
	while (cur)
	{
		if (cur->to == to)
		{
			if (prev)
				prev->next = cur->next;
			else
				*edge_list = cur->next;
			tmp = cur;
			cur = cur->next;
			xfree(tmp, sizeof(Edge));
			break;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

static void	add_path(int **matrix, Euler_ctx *ctx)
{
	PathNode *head;
	int from, to;

	head = ctx->head;
	from = 0;
	to = 0;
	while (head->next)
	{
		from = head->v->id;
		to = head->next->v->id;
		matrix[from][to] = matrix[to][from] = 1;
		delete_edge(&ctx->vs[from]->incidence, to);
		delete_edge(&ctx->vs[to]->incidence, from);
		head = head->next;
	}
}

int		make_eulerian(int **matrix, int n)
{
	Euler_ctx ctx;
	Edge *edge;
	// print_matrix(matrix, n, n);

    ctx.degree = xmalloc(sizeof(int) * n);
    ctx.visited = xcalloc(n, sizeof(int));
    if (!ctx.degree)
        return -1;
    compute_degrees(matrix, n, ctx.degree);     // -> graph_analysis.c
	if (need_double_edge(ctx.degree, n))
	{
		free_ctx(&ctx, n);
		return 0;
	}

    ctx.vs = comp_adj_list(matrix, n, 1); // -> graph_conversions.c
	if (!ctx.vs)
	{
		free_ctx(&ctx, n);
		return -1;
	}
    int i;
    for (i = 0; i < n; i++)
    {
        if (ctx.degree[i] % 2 == 0) continue;
        edge = ctx.vs[i]->incidence;
		if (!edge)
		{
			free_ctx(&ctx, n);
			return -2;
		}
		memset(ctx.visited, 0, sizeof(int) * n);
		ctx.head = NULL;
		ctx.start = edge->from;
		ctx.visited[edge->from] = 1;
		if (backtrack_euler(&ctx, edge->from))
		{
			add_path(matrix, &ctx);
			// print_matrix(matrix, n, n);
		}
		compute_degrees(matrix, n, ctx.degree);
		free_path(ctx.head);
    }
	free_ctx(&ctx, n);
	return 1;
}
