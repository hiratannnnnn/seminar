#ifndef TYPES_H
# define TYPES_H

/* ========= Data Structure =========*/

typedef struct 	Edge
{
    int         id;			// edge_id
    int         from;   	// vertex from
    int         to;     	// vertex to
    int         used;		// for any extra uses
    struct Edge *next;		// for edge list
}               Edge;

typedef struct 	Vertex
{
    int         id;			// vertex id
    Edge        *incidence;	// incidence list (edge list)
}               Vertex;

typedef struct 	Node
{
    int         edge_id; 	// edge id
    struct Node *prev;		// prev node
    struct Node *next;		// next node
}               Node;

typedef struct 	PathNode
{
    int             vertex;	// vertex id
    struct PathNode *prev;	// prev node
    struct PathNode *next;	// next node
}				PathNode;

#endif
