#ifndef TYPES_H
# define TYPES_H

/* ========= Data Structure =========*/

typedef struct Edge
{
    int         id;
    int         from;
    int         to;
    int         used;
    struct Edge *next;
}               Edge;

typedef struct Vertex
{
    int         id;
    Edge        *incidence;
}               Vertex;

typedef struct Node
{
    int         edge_id;
    struct Node *prev;
    struct Node *next;
}               Node;

typedef struct PathNode
{
    int             vertex;
    struct PathNode *next;
}                   PathNode;

#endif
