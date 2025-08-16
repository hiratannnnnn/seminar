#include "path.h"

Heap *heap_create(int capacity, HeapCmp cmp)
{
    Heap *h;

    h = xmalloc(sizeof(Heap));
    if (!h)
        return NULL;
    h->array = xmalloc(sizeof(void *) * capacity);
    if (!h->array)
        return (free_heap_node(h, capacity), NULL);
    h->size = 0;
    h->capacity = capacity;
    h->cmp = cmp;
    return h;
}

void heap_push(Heap *h, void *item)
{
    int i;
    void *tmp;

    i = h->size++;
    h->array[i] = item;
    while (i > 0 && h->cmp(h->array[(i-1)/2], h->array[i]) > 0)
    {
        tmp = h->array[i];
        h->array[i] = h->array[(i-1)/2];
        h->array[(i-1)/2] = tmp;
        i = (i-1)/2;
    }
}

void *heap_pop(Heap *h)
{
    void *min;
    void *tmp;
    int i, left, right, smallest;

    min = h->array[0];
    h->array[0] = h->array[--h->size];
    i = 0;
    while (1)
    {
        left = 2 * i + 1;
        right = 2 * i + 2;
        smallest = i;
        if (left < h->size && h->cmp(h->array[left], h->array[smallest]) < 0)
            smallest = left;
        if (right < h->size && h->cmp(h->array[right], h->array[smallest]) < 0)
            smallest = right;
        if (smallest == i)
            break;
        tmp = h->array[i];
        h->array[i] = h->array[smallest];
        h->array[smallest] = tmp;
        i = smallest;
    }
    return min;
}

void    free_heap_node(Heap *h, int capacity)
{
    int i;
    Node *node;

    if (h->array)
    {
        for (i = 0; i < h->size; i++)
        {
            node = (Node *)h->array[i];
            if (node)
                free_node(node);
        }
        xfree(h->array, sizeof(void *) * capacity);
    }
    xfree(h, sizeof(Heap));
}

void *heap_peek(Heap *h)
{
    if (h->size == 0)
    {
        return NULL;
    }
    return h->array[0];
}

void heap_clear(Heap *h)
{
    int i;
    Node *node;

    for (i = 0; i < h->size; i++)
    {
        node = (Node *)h->array[i];
        if (node)
            free_node(node);
    }
    h->size = 0;
}

int heap_cmp_edgecost(const void *a, const void *b)
{
    const Node *n_a = (const Node *)a;
    const Node *n_b = (const Node *)b;
    Edge *e_a, *e_b;

    e_a = node_get_edge(n_a);
    e_b = node_get_edge(n_b);
    if (!e_a || !e_b)
        return (printf("got null \n"), 0);
    if (e_a->cost < e_b->cost)
        return (-1);
    else if (e_a->cost > e_b->cost)
        return (1);
    else
        return (e_a->id - e_a->id);
}
