#include "../jung.h"

Node	*create_node(int edge_id)
{
	Node	*node;

	node = (Node *)malloc(sizeof(Node));
	if (!node)
		return (NULL);
	node->edge_id = edge_id;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	append_node(Node **head, Node *new_node)
{
	Node	*cur;

	if (!head || !new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new_node;
	new_node->prev = cur;
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


