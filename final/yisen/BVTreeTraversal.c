#include <stddef.h>
#include "bouncingBoxTree.h"
#include "BVTreeTraversal.h"

void Push(Stack **s,Node *a, Node *b)
{
//	printf("Push\n");
	Stack *node=(Stack *)malloc(sizeof(Stack));
	node->node1=a;
	node->node2=b;
	if ((*s)==NULL) {
		(*s)=node;
		node->next=NULL;
		node->prev=NULL;
	} else {
		node->prev=(*s);
		node->next=NULL;
		(*s)->next=node;
		(*s)=node;
	}
	
}
void Pop(Stack **s, Node** a, Node **b)
{
	Stack *t;
//	printf("Pop\n");
	(*a)=(*s)->node1;
	(*b)=(*s)->node2;
	t=(*s);
	(*s)=(*s)->prev;
	free(t);
}
int isEmpty(Stack *s)
{
	if (s==NULL) 
	return(1);
	else
	return(0);
}
int isLeaf(Node *a)
{
	if (a->type==LEAF) 
	return(1);
	else 
	return(0);
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
	if (v1>=v2) return(1); 
	else return(0);
	
}
int descendA(Node *a, Node *b)
{
	/* return 1 if descend a*/
	int i;
	if (isLeaf(b)) i=1;
	  else {
	if (isLeaf(a)) i=0;
	  else
    {
	  if (compareAABB(&a->BV,&b->BV) == 1)
	  i=1;
	  else
	  i=0;
    }
   }
	return i;
}
void BVTreeTraversal(CollisionResult *r, Node *Tri, Node *Sph)
{

	Stack *s= NULL;
	while (1) {
	//	printf("in\n");
	//	printAABB(Tri->BV);
	//	printf("\n");
	//    printAABB(Sph->BV);
	//    printf("==========\n");
	//    printf("%d\n",Tri->type );
//	printf("\nLoop begin\n");
//	printf("Tri objects number%d\n",Tri->numObject);
	//printf("Sph objects number%d\n",Sph->numObject);
//	printf("Type  %d %d result %d collision %d\n",Tri->type,Sph->type,(isLeaf(Tri) && isLeaf(Sph) ),TestAABB(Tri->BV,Sph->BV));
//	printAABB(Tri->BV);printAABB(Sph->BV);
//	printf("AABB %d\n",TestAABB(Tri->BV,Sph->BV));
    if (TestAABB(Tri->BV,Sph->BV)==3)
	{
		printAABB(Tri->BV);printAABB(Sph->BV);
        printf("AABB %d\n",TestAABB(Tri->BV,Sph->BV));
	 } 
		if (TestAABB(Tri->BV,Sph->BV)==0) {
			if (isLeaf(Tri) && isLeaf(Sph) ) {
			//	printf("boom!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				//CollideObject(r,Tri,Sph);
			} else {
			//	printf("descend\n");
				if (descendA(Tri,Sph)) {
			//		printf("Descend A Type %d %d\n",Tri->type,Sph->type);
					Push(&s,Tri->right,Sph);
					Tri=Tri->left;
					
					continue;
				} else {
			//		printf("Descend B Type %d %d\n",Tri->type,Sph->type);
					Push(&s,Tri,Sph->right);
					Sph=Sph->left;
					
					//printf("Fuck\n");
					continue;
				}
			}
		} 
    //    printf("%d\n",isEmpty(s));
		if (isEmpty(s)) break;
		Pop(&s,&Tri,&Sph);
	}
	
} 
