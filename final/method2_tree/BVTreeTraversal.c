///Yisen Wang
#include <stddef.h>
#include "bouncingBoxTree.h"
#include "BVTreeTraversal.h"


void Push(Stack **s,Node *a, Node *b)
{
/**	
Stack implementation: push Node a and Node b into Stack c 
*/
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
/**	
Stack implementation: Pop stack element into a  and b
*/
	Stack *t;
	(*a)=(*s)->node1;
	(*b)=(*s)->node2;
	t=(*s);
	(*s)=(*s)->prev;
	free(t);
}

int isEmpty(Stack *s)
{
/**	
Stack implementation: Check is Stack empty
*/
	if (s==NULL) 
	return(1);
	else
	return(0);
}

int isLeaf(Node *a)
{
/**	
Traversal implementation: Check type of Node a, return 1 if a is LEAF 
*/
	if (a->type==LEAF) 
	return(1);
	else 
	return(0);
}

int compareAABB(AABB *box1, AABB *box2)
{
/** 
AABB implementation: Compare the volumn of two bouncing box
return 1 if box1>box2 
*/
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
/** 
Traversal implementation: Decide which child to descend into
return 1 if descend into Node a first 
*/
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
void BVTreeTraversal( Node *Tri, Node *Sph, double *TriangleData, double *SphereData, CollisionResult *r, int *lenResults)
{
/**	
Traversal implementation: Traversal two bouncing volumn trees
Argument: Tri: bouncing volumn tree for triangle mesh 
          Sph: bouncing volumn tree for Sphere
		  TriangleData, SphereData: pointer to original data
		  CollisionResult *r: List for storing result 
   
*/
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
				//CollideObject(r,Tri,Sph);
				int indexTri=Tri->object[0];
				int indexSph=Sph->object[0];
				double *pTri=&TriangleData[indexTri*9];
				double *pSph=&SphereData[indexSph*4];
				int result=colli(pTri,pSph);
				if (result)
				  {
				  	*lenResults=(*lenResults)+1; 
				  	CollisionResult* newResult=(CollisionResult*)malloc(sizeof(CollisionResult));
				  	newResult->next=NULL;
				  	r->next=newResult;
				  	r->tri=indexTri;
				  	r->sph=indexSph;
				  	r=newResult;
				  } 
			} else {
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

void DirectTraversal( double *TriangleData, int tri_num,double *SphereData,int sph_num, int *lenResults)
{
/**
Traversal implementation: Brute force traversal
*/
	int i,j;
	for (i=0;i<tri_num;i++)
	for (j=0;j<sph_num;j++)
	{
		int indexTri=i;
		int indexSph=j;
		double *pTri=&TriangleData[indexTri*9];
		double *pSph=&SphereData[indexSph*4];
		int result=colli(pTri,pSph);
		if (result)
			{
			*lenResults=(*lenResults)+1; 
			//CollisionResult* newResult=(CollisionResult*)malloc(sizeof(CollisionResult));
			//newResult->next=NULL;
			//r->next=newResult;
			//r->tri=indexTri;
			//r->sph=indexSph;
			//r=newResult;
			} 
	}
}

void getBox(Node *treeTri, int deep, double *boxes, int *index)
{
/**
Debug purpose: Print bouncing Box for first k level bouncing tree
               
*/
	if (deep>0)
	{
		AABB a=treeTri->BV;
		for (int i=0;i<3;i++) {
				boxes[(*index)]=a.min[i];
				boxes[(*index)+1]=a.max[i];
				*index=*index+2;
			}
		if (treeTri->left != NULL)  getBox(treeTri->left,deep-1,boxes,index);
		if (treeTri->right != NULL) getBox(treeTri->right,deep-1,boxes,index);
	} 
}

void printList(FILE *f3, CollisionResult *r,int len,double time)
{
/**
Print results of collision detection into file f3
*/
	fprintf(f3,"%d %f\n",len,time);
	CollisionResult *t;
	for (int i;i<len;i++)
	  {
	  	t=r->next;
	  	fprintf(f3,"%d %d\n",r->tri,r->sph); 
	  	free(r);
	  	r=t;
	  }
}

