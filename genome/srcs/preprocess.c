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
	int *perm_sent, *sigma_sent;
	int n, n_sent, i, id, prev_id;

	M_stack = create_stack_node((ctx->n) + 1);
	m_stack = create_stack_node(0);
	if (!M_stack || !m_stack)
		return (-1);
	n = ctx->n;
	n_sent = ctx->n_sent;
	perm_sent = ctx->perm_sent;
	sigma_sent = ctx->sigma_sent;
	i = 0;
	while (i < n_sent)
	{
		maxes[i] = n + 1;
		mins[i] = 0;
		i++;
		while (!(perm_sent[i] * sigma_sent[i] != n + 1 ||
				(perm_sent[i] == 0 && sigma_sent[i] == -1)))
		{
			printf("%d\n", i);
			id = perm_sent[i];
			prev_id = perm_sent[i - 1];
			if (prev_id > id)
				push_stack(&M_stack, prev_id);
			else
				pop_stack_thres(&M_stack, id, -1);
			maxes[i] = peek_stack(M_stack);
			if (prev_id < id)
				push_stack(&m_stack, prev_id);
			else
				pop_stack_thres(&m_stack, id, 1);
			mins[i] = peek_stack(m_stack);
			i++;
		}
		maxes[i] = n + 1;
		mins[i] = 0;
		i++;
	}
	free_stack(M_stack);
	free_stack(m_stack);
	return (1);
}
