#include "sorting.h"

void	sort_list(Edge **head, int (*cmp)(int, int))
{
	Edge *ptr1, *lptr, *prev, *tmp;
	int swapped;

	if (!head || !*head)
		return ;
	lptr = NULL;
	do
	{
		// print_edge_list(*head);
		swapped = 0;
		ptr1 = *head;
		prev = NULL;
		while (ptr1->next != lptr)
		{
			if (cmp(ptr1->to, ptr1->next->to) > 0)
			{
				// printf("[DEBUG] swapping %d, %d\n", ptr1->to, ptr1->next->to);
				tmp = ptr1->next;
				ptr1->next = tmp->next;
				tmp->next = ptr1;
				if (prev)
					prev->next = tmp;
				else
					*head = tmp;
				swapped = 1;
				prev = tmp;
			}
			else
			{
				prev = ptr1;
				ptr1 = ptr1->next;
			}
		}
		lptr = ptr1;
	} while (swapped);
}

void	sort_list_by_degree(Edge **head, int *degree, int (*cmp)(int, int))
{
	Edge *ptr1, *lptr, *tmp, *prev;
	int swapped;

	if (!head || !*head)
		return ;
	lptr = NULL;
	do
	{
		swapped = 0;
		ptr1 = *head;
		prev = NULL;
		while (ptr1->next != lptr)
		{
			if (cmp(degree[ptr1->to], degree[ptr1->next->to]) > 0)
			{
				tmp = ptr1->next;
				ptr1->next = tmp->next;
				tmp->next = ptr1;
				if (prev)
					prev->next = tmp;
				else
					*head = tmp;
				swapped = 1;
				prev = tmp;
			}
			else
			{
				prev = ptr1;
				ptr1 = ptr1->next;
			}
		}
		lptr = ptr1;
	} while (swapped);

}
