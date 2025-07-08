#include "lib.h"

static int 		add_cycles_until_ratio	(int **matrix, Euler_ctx *ctx, int n, double edge_ratio);
static void		add_path				(int **matrix, Euler_ctx *ctx);
static int		backtrack_euler			(Euler_ctx *ctx, int cur);
static int		backtrack_euler_cycle	(Euler_ctx *ctx, int cur);
static void		delete_edge				(Edge **edge_list, int to);
static int		euler_ctx_init			(Euler_ctx *ctx, int **matrix, int n);
static void 	free_ctx				(Euler_ctx *ctx, int n);

int		make_eulerian(int **matrix, int n, double edge_ratio)
{
	Euler_ctx ctx;
	Edge *edge;
    int i, init;

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
		free_pathnode(&ctx.head);
    }
	add_cycles_until_ratio(matrix, &ctx, n, edge_ratio);
	free_ctx(&ctx, n);
	return 1;
}

int 	**generate_random_euler(int n, double edge_ratio)
{
	int **matrix;

	matrix = generate_random_tree(n);
	if (make_eulerian(matrix, n, edge_ratio) < 0)
		return (NULL);
	return matrix;
}

static int add_cycles_until_ratio(int **matrix, Euler_ctx *ctx, int n, double edge_ratio)
{
	int total, max_edges, cur_edges, i, found;

	total = n * (n - 1) / 2;
	max_edges = (int)(edge_ratio * total);
	while (1)
	{
		cur_edges = count_edges(ctx->degree, n);
		if (cur_edges >= max_edges)
			break;
		found = 0;
		for (i = 0; i < n && !found; i++)
		{
			if (ctx->degree[i] < n - 1)
			{
				memset(ctx->visited, 0, sizeof(int) * n);
				ctx->head = NULL;
				ctx->start = i;
				ctx->visited[i] = 1;
				if (backtrack_euler_cycle(ctx, i))
				{
					add_path(matrix, ctx);
					compute_degrees(matrix, n, ctx->degree);
					free_pathnode(&ctx->head);
					found = 1;
				}
				else
				{
					free_pathnode(&ctx->head);
				}
			}
		}
		if (!found)
			break;
	}
	return (1);
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
static int	backtrack_euler_cycle(Euler_ctx *ctx, int cur)
{
	Vertex		*v;
	Edge		*edge;
	int			length;

	sort_list_by_degree(&ctx->vs[cur]->incidence, ctx->degree, cmp_int_asc);
	v		= ctx->vs[cur];
	edge	= v->incidence;
	append_pathnode(&ctx->head, create_pathnode(v));
	length	= count_pathnodes(ctx->head);
	if (length > 3 && cur == ctx->start)
		return (1);
	while (edge)
	{
		if (!ctx->visited[edge->to])
		{
			ctx->visited[edge->to] = 1;
			if (backtrack_euler_cycle(ctx, edge->to))
			{
				return (1);
			}
			ctx->visited[edge->to] = 0;
			pathnode_pop_last(&ctx->head);
		}
		else if (edge->to == ctx->start && length > 2)
		{
			append_pathnode(&ctx->head, create_pathnode(ctx->vs[ctx->start]));
			return (1);
		}
		edge = edge->next;
	}
	return (0);
}

static int	backtrack_euler(Euler_ctx *ctx, int cur)
{
    Vertex      *v;
    Edge        *edge;
    int         length;

	sort_list_by_degree(&ctx->vs[cur]->incidence, ctx->degree, cmp_int_asc);
    v       = ctx->vs[cur];
    edge    = v->incidence;
    append_pathnode(&ctx->head, create_pathnode(v));
    length  = count_pathnodes(ctx->head);
	if (length > 1 && ctx->degree[cur] % 2 == 1)
		return 1;
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

/**
 * @return -2 malloc error nado
 * @return -1 impossible to make eulerian
 * @return 1  success
 */
static int	euler_ctx_init(Euler_ctx *ctx, int **matrix, int n)
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
		free_pathnode(&ctx->head);
}
