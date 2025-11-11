# include "genome.h"

void 	free_stack_node(Stack_int *node)
{
	xfree(node, sizeof(Stack_int));
}

void	free_stack(Stack_int *head)
{
	Stack_int *cur, *tmp;

	cur = head;
	while (cur)
	{
		tmp = cur->next;
		free_stack_node(cur);
		cur = tmp;
	}
}

Stack_int *create_stack_node(int nbr)
{
	Stack_int *node;

	node = (Stack_int *)xmalloc(sizeof(Stack_int) * 1);
	if (!node)
		return (NULL);
	node->nbr = nbr;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void push_stack(Stack_int **head, int nbr)
{
	Stack_int *node;

	if (!head)
		return ;
	node = create_stack_node(nbr);
	if (!node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	node->next = *head;
	(*head)->prev = node;
	*head = node;
}

Stack_int *pop_stack(Stack_int **head)
{
	Stack_int *cur;

	if (!head || !(*head))
		return (NULL);
	cur = (*head);
	*head = cur->next;
	if (*head)
		(*head)->prev = NULL;
	cur->next = NULL;
	return (cur);
}

int 	peek_stack(Stack_int *head)
{
	if (!head)
		return (INT_MIN);
	return (head->nbr);
}
