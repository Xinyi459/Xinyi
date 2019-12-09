#include <stddef.h>
#include "bouncingBoxTree.h"
#include "BVTreeTraversal.h"

void Push(Stack *s,Node *a, Node *a)
{
	node=(Stack *)malloc(sizeof(Stack));
	if (s==NULL) {
		s=node;
		s->next=NULL;
		s->prev=NULL;
		s->node1=a;
		s->node2=b;
	} else {
		node->prev=s;
		node->next=NULL;
		s->next=node;
		node->node1=a;
		node->node2=b;
		s=node;
	}
	return s;	
}
void Pop(Stack *s, Node* a, Node *b)
{
	a=s->node1;
	b=s->node2;
	s=s->prev;
	return s;
}
int isEmpty(Stack *s)
{
	if (s==NULL) return 1
	else return 0;
}
int isLeaf(Node *a)
{
	if a->type=LEAF return 1
	else return 0;
}

int compareAABB(AABB *box1, AABB *box2)
{
	/* return 1 if box1>box2 */
	float v1=1,v2=1;
	for (size_t i;i<3;i++)
	{
		v1 *=(box1->max[i]-box1->min[i]);
	    v2 *=(box2->max[i]-box2->min[i]);
	}
	if (v1>=v2) return 1 
	else return 0;
	
}
int descendA(Node *a, Node *b)
{
	/* return 1 if descend a*/
	if (isLeaf(b)) return 1;
	if (isLeaf(a)) return 0;
	if 
}
void BVTreeTraversal(CollisionResults *r, Node *Tree1, Node *Tree2)
{

	Stack *s= NULL;
	while (1) {
		if (!TestAABB(Tree1->BV,Tree2->BV)) {
			if (isLeaf(a) && isLeaf(b) ) {
				CollideObject(r,a,b);
			} else {
				if (descendA(a,b)) {
					Push(s,a->right,b);
					a=a->left;
					continue;
				} else {
					Push(s,b->right);
					b=b->left;
					continue;
				}
			}
		} 
		
		if (isEmpty(s)) break;
		Pop(s,a,b);
	}
	
} 
