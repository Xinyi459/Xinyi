#ifndef BVTreeTraversal_H
#define BVTreeTraversal_H
#include "bouncingBoxTree.h"
/**
 * Definition of Stack \n 
 * node1 and node2 for storing two BV tree node  
 */
typedef struct Stack_def
{
	Node *node1;
	Node *node2;
	struct Stack_def *next;
	struct Stack_def *prev;
} Stack; 

/**
 * Single linked list for storing collision result \n 
 * tri,sph for storing the index of triangle and sphere \n 
 */
typedef struct CollisionResult_def{
	int tri;
	int sph;
	struct CollisionResult_def* next;
} CollisionResult;
void Push(Stack **s,Node *a, Node *b);
void Pop(Stack **s, Node** a, Node **b);
int isEmpty(Stack *s);
int isLeaf(Node *a);
int compareAABB(AABB *box1, AABB *box2);
int descendA(Node *a, Node *b);
void BVTreeTraversal( Node *Tri, Node *Sph, double *TriangleData, 
                      double *SphereData, CollisionResult *r, 
					  int *lenResults);
void DirectTraversal( double *TriangleData, int tri_num,
                      double *SphereData,int sph_num, int *lenResults);
void getBox(Node *treeTri, int deep, double *boxes, int *index);
void printList(FILE *f3, CollisionResult *r,int len,double time);
#endif
