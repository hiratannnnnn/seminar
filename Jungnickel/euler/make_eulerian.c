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
	if (ctx->head)
		free_path(&ctx->head);
}

static int	backtrack_euler(Euler_ctx *ctx, int cur)
{
    Vertex      *v;
    Edge        *edge;
    PathNode    *node;
    int         length;

	sort_list_by_degree(&ctx->vs[cur]->incidence, ctx->degree, cmp_int_asc);
    v       = ctx->vs[cur];
    edge    = v->incidence;
    node    = create_pathnode(v);
    append_pathnode(&ctx->head, node);
    length  = pathnode_length(ctx->head);

	if (length > 1 && ctx->degree[cur] % 2 == 1)
	{
		return 1;
	}

    while (edge)
    {
        if (!ctx->visited[edge->to])
        {
			ctx->visited[edge->to] = 1;
			if (backtrack_euler(ctx, edge->to))
				return (1);
			ctx->visited[edge->to] = 0;
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

/**
 * @return -2 malloc error nado
 * @return -1 impossible to make eulerian
 * @return 1  success
 */

int		euler_ctx_init(Euler_ctx *ctx, int **matrix, int n)
{
	ctx->degree = xmalloc(sizeof(int) * n);
	if (!ctx->degree)
		return (-2);
	compute_degrees(matrix, n, ctx->degree);
	ctx->visited = xmalloc(sizeof(int) * n);
	ctx->vs = comp_adj_list(matrix, n, 1);
	if (!ctx->visited || !ctx->vs)
		return (free_ctx(ctx, n), -2);
	ctx->head = NULL;
	if (need_double_edge(ctx->degree, n))
	{
		return (free_ctx(ctx, n), -1);
	}
	return (1);
}

int		make_eulerian(int **matrix, int n)
{
	Euler_ctx ctx;
	Edge *edge;
    int i;
	int init;
	init = euler_ctx_init(&ctx, matrix, n);
	if (init < 1)
		return init;
    for (i = 0; i < n; i++)
    {
        if (ctx.degree[i] % 2 == 0) continue;
        edge = ctx.vs[i]->incidence;
		if (!edge)
			return(free_ctx(&ctx, n), -2);
		memset(ctx.visited, 0, sizeof(int) * n);
		ctx.head = NULL;
		ctx.start = edge->from;
		ctx.visited[edge->from] = 1;
		if (backtrack_euler(&ctx, edge->from))
			add_path(matrix, &ctx);
		compute_degrees(matrix, n, ctx.degree);
		free_path(&ctx.head);
    }
	free_ctx(&ctx, n);
	return 1;
}
