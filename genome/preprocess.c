# include "genome.h"

static void	pop_stack_thres(Stack_int **head, int thres, int sign)
{
	Stack_int *cur;

	cur = *head;
	while (cur)
	{
		if (sign == -1 && cur->nbr < thres)
		{
			cur = pop_stack(head);
			free_stack_node(cur);
		}
		else if (sign == 1 && cur->nbr > thres)
		{
			cur = pop_stack(head);
			free_stack_node(cur);
		}
		else
			break;
		cur = *head;
	}
}

int preprocess(Extremity_ctx *ctx, int *maxes, int *mins)
{
	Stack_int *M_stack, *m_stack;
	int *perm;
	int n, i, id, prev_id;

	M_stack = create_stack_node((ctx->n) + 1);
	m_stack = create_stack_node(0);
	if (!M_stack || !m_stack)
		return (-1);
	n = ctx->n;
	perm = ctx->perm;
	maxes[0] = maxes[n + 1] = n + 1;
	mins[0] = mins[n + 1] = 0;
	maxes[1] = n + 1;
	mins[1] = 0;
	for (i = 1; i < n; i++)
	{
		id = abs(perm[i]);
		prev_id = abs(perm[i - 1]);
		// print_stack(M_stack);
		if (prev_id > id)
			push_stack(&M_stack, prev_id);
		else
			pop_stack_thres(&M_stack, id, -1);
		maxes[i+1] = peek_stack(M_stack);
		if (prev_id < id)
			push_stack(&m_stack, prev_id);
		else
			pop_stack_thres(&m_stack, id, 1);
		mins[i+1] = peek_stack(m_stack);
	}
	free_stack(M_stack);
	free_stack(m_stack);
	return (1);
}
