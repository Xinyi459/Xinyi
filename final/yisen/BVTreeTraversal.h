#ifndef BVTreeTraversal_H
#define BVTreeTraversal_H
#include "bouncingBoxTree.h"
typedef struct Stack_def
{
	Node *node1;
	Node *node2;
	struct Stack_def *next;
	struct Stack_def *prev;
} Stack; 

typedef struct result_def
{
	int tri;
	int sph;  
} CollisionResult;
#endif
