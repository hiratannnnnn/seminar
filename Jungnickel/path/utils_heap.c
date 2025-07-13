#include "path.h"

Heap *heap_create(int capacity, HeapCmp cmp)
{
    Heap *h = xmalloc(sizeof(Heap));
    h->array = xmalloc(sizeof(void *) * capacity);
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

void    heap_free(Heap *h, int capacity)
{
    xfree(h->array, sizeof(void *) * capacity);
    xfree(h, sizeof(Heap));
}