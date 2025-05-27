#include "lib.h"

Node	*create_node(Edge *edge)
{
	Node	*node;

	node = (Node *)xmalloc(sizeof(Node));
	if (!node)
		return (NULL);
	node->edge = edge;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	append_node(Node **head, Node *new_node)
{
	Node	*last;

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

void	insert_node_after(Node *pos, Node *new_node)
{
	if (!pos || !new_node)
		return ;
	new_node->next = pos->next;
	new_node->prev = pos;
	if (pos->next)
		pos->next->prev = new_node;
	pos->next = new_node;
}

Node *get_last_node(Node *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return head;
}

Node	*node_pop_first(Node **head)
{
	Node *first;

	if (!head || !*head)
		return (NULL);
	first = *head;
	*head = first->next;
	if (*head)
		(*head)->prev = NULL;
	return first;
}

void	free_node_list(Node *head)
{
	Node	*cur;
	Node	*next;

	cur = head;
	while (cur)
	{
		next = cur->next;
		xfree(cur, sizeof(Node));
		cur = next;
	}
}
