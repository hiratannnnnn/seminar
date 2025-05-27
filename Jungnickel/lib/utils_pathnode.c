#include "lib.h"

PathNode 	*create_pathnode(Vertex *vertex)
{
	PathNode 	*node;

	node = (PathNode *)xmalloc(sizeof(PathNode));
	if (!node)
		return NULL;
	node->v = vertex;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void		append_pathnode(PathNode **head, PathNode *new_pathnode)
{
	PathNode	*last;

	if (!head || !new_pathnode)
		return ;
	if (*head == NULL)
	{
		*head = new_pathnode;
		return ;
	}
	last = get_last_pathnode(*head);
	last->next = new_pathnode;			// append to the last
	new_pathnode->prev = last;
}

void		insert_pathnode_after(PathNode *pos, PathNode *new_pathnode)
{
	if (!pos || !new_pathnode)
		return ;
	new_pathnode->next = pos->next;
	new_pathnode->prev = pos;
	if (pos->next)
		pos->next->prev = new_pathnode;
	pos->next = new_pathnode;
}

PathNode	*get_last_pathnode(PathNode *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return head;
}

PathNode 	*pathnode_pop_first(PathNode **head)
{
	PathNode *first;

	if (!head || !*head)
		return (NULL);
	first = *head;
	*head = first->next;
	if (*head)
		(*head)->prev = NULL;
	return first;
}

void 	free_path(PathNode *path)
{
    PathNode *temp;

    while (path)
    {
        temp = path;
        path = path->next;
        xfree(temp, sizeof(PathNode));
    }
}
