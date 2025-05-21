#include "lib.h"

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

/**
 * @brief Returns the last node of a doubly linked list.
 *
 * @param head Pointer to the head node of the list
 * @return Pointer to the last node, or NULL if the list is empty
 */

Node *get_last_node(Node *head)
{
	if (!head)
		return NULL;
	while (head->next)
		head = head->next;
	return head;
}
