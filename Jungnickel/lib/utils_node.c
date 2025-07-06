#include "lib.h"

EdgeNode	*create_edgenode(Edge *edge)
{
	EdgeNode	*node;

	node = (EdgeNode *)xmalloc(sizeof(EdgeNode));
	if (!node)
		return (NULL);
	node->edge = edge;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	append_node(EdgeNode **head, EdgeNode *new_node)
{
	EdgeNode	*last;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	last = get_last_node(*head);
	last->next = new_node;
	new_node->prev = last;
}

void	insert_node_after(EdgeNode *pos, EdgeNode *new_node)
{
	if (!pos || !new_node)
		return ;
	new_node->next = pos->next;
	new_node->prev = pos;
	if (pos->next)
		pos->next->prev = new_node;
	pos->next = new_node;
}

EdgeNode 	*get_last_node(EdgeNode *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return head;
}

EdgeNode	*node_pop_first(EdgeNode **head)
{
	EdgeNode *first;

	if (!head || !*head)
		return (NULL);
	first = *head;
	*head = first->next;
	if (*head)
		(*head)->prev = NULL;
	return first;
}

void	free_node_list(EdgeNode *head)
{
	EdgeNode	*cur;
	EdgeNode	*next;

	cur = head;
	while (cur)
	{
		next = cur->next;
		xfree(cur, sizeof(EdgeNode));
		cur = next;
	}
}
