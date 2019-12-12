#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include "bouncingBoxTree.h"

Triangle * TriangleData;

void printAABB(AABB a)
{
	int i;
	for (i=0;i<3;i++)
	  printf("%f %f\n",a.min[i],a.max[i]);
}

void setAABB(AABB *a)
{
	int i;
	for (i=0;i<3;i++) {
	    a->min[i]=0;
		a->max[i]=0;
	}

}
void printArr(int *a,int n)
{
	int i;
	for (i=0;i<n;i++)
	  printf("%d ",a[i]);
	printf("\n");
}

double maxIndex(double x, double y, double z)
{
	if (x>=y && x>=z ) return 0;
	if (y>=x && y>=z ) return 1;
	if (z>=x && z>=y ) return 2;
}

double max(double x, double y, double z)
{
	if (x>=y && x>=z ) return x;
	if (y>=x && y>=z ) return y;
	if (z>=x && z>=y ) return z;
}

double min(float x, float y, float z)
{
	if (x<=y && x<=z ) return x;
	if (y<=x && y<=z ) return y;
	if (z<=x && z<=y ) return z;
}

int TestAABB(AABB a,AABB b)
{
	/*
	return 0 if two AABB are intersected.
	*/
	if (a.max[0] < b.min[0] || a.min[0] > b.max[0]) return 0;
	if (a.max[1] < b.min[1] || a.min[1] > b.max[1]) return 0;
	if (a.max[2] < b.min[2] || a.min[2] > b.max[2]) return 0;
	return 1;
}

int findNodeToPut(float mean, float minCoordinate,float maxCoordinate, int num1, int num2)
{
	if (maxCoordinate < mean ) return LEFT;
	if (minCoordinate > mean ) return RIGHT;
	if (maxCoordinate > mean && minCoordinate < mean)
	  if (num1>=num2) { return RIGHT; }
	  else { return LEFT; }
}

void updateBouncingBoxTri(double *TriangleData,int index,AABB *pBV)
{
//	printf("innnnnnnnnnnnnn\n");
	if (pBV->max[0]-pBV->min[0] < MIN_SIZE &&
	   pBV->max[1]-pBV->min[1]  < MIN_SIZE && 
	   pBV->max[2]-pBV->min[2]  < MIN_SIZE) {
	    for (size_t i=0; i<3; i++) {
	      pBV->min[i]=min(TriangleData[index*9+i],
	                     TriangleData[index*9+3+i],
				         TriangleData[index*9+6+i]);
	      pBV->max[i]=max(TriangleData[index*9+i],
	                     TriangleData[index*9+3+i],
				         TriangleData[index*9+6+i]);
	    }
	    for (size_t i=0; i<3; i++)
	      if ( pBV->max[i]-pBV->max[i]<MIN_SIZE) {
	        pBV->min[i] -= MIN_SIZE;	
	        pBV->max[i] += MIN_SIZE;
		    }
	} else {
        for (size_t i=0; i<3; i++) {
	      float tmin=min(TriangleData[index*9+i],
	                     TriangleData[index*9+3+i],
				         TriangleData[index*9+6+i]);
		  pBV->min[i]=min(pBV->min[i],tmin,INT_MAX);
	      double tmax=max(TriangleData[index*9+i],
	                      TriangleData[index*9+3+i],
				          TriangleData[index*9+6+i]);
		  pBV->max[i]=max(pBV->max[i],tmax,INT_MIN);
	    }
	}
}

int partitionObjectsTri(double *TriangleData,
                        int *objects, int *tobjects,
						int numObjects, 
						AABB BV, 
						AABB *pBVleft, 
						AABB *pBVright)
{
	int index=maxIndex(abs(BV.min[0]-BV.max[0]),
	              abs(BV.min[1]-BV.max[1]),
	              abs(BV.min[2]-BV.max[2])
	);
	printf("Partition index= %d\n",index); 
	int i, j, k, x, y, t;
	double mean=0;
	for (i=0;i<numObjects;i++) {
	    mean += TriangleData[objects[i]*9+index];
	    mean += TriangleData[objects[i]*9+3+index];
	    mean += TriangleData[objects[i]*9+6+index];
	}
	mean /= numObjects * 3;
	x=0;y=numObjects-1;
	for (i=0; i<numObjects; i++)
	{
		double maxCoordinate = max(TriangleData[objects[i]*9+index] , 
		                    TriangleData[objects[i]*9+3+index] , 
					        TriangleData[objects[i]*9+6+index]);
		double minCoordinate = min(TriangleData[objects[i]*9+index] , 
		                    TriangleData[objects[i]*9+3+index] , 
					        TriangleData[objects[i]*9+6+index]);
		
		int r=findNodeToPut(mean, minCoordinate,maxCoordinate, x+1, numObjects-y);
		
		if (r==LEFT ) {
			// put into left node
			tobjects[x++] = objects[i];
			updateBouncingBoxTri(TriangleData,objects[i], pBVleft);
		} else
		if (r==RIGHT) {
			// put into right node
			tobjects[y--] = objects[i];
			updateBouncingBoxTri(TriangleData,objects[i], pBVright); 
		}
	}
	for (i=0; i<numObjects; i++)
	objects[i]=tobjects[i];
	return(x);
}

void buildBVTreeTri(double *TriangleData, 
                    Node **tree, 
					int *objects, int *tobjects, 
					int numObjects, AABB BV,int *debug)
{
	//assert(numObjects>0);
	printf("\nNumber of Objects in this node %d\n Objects index ",numObjects);
	printArr(objects,numObjects);
	Node *pNode=(Node*)malloc(sizeof(Node));
    AABB BVleft, BVright;
    setAABB(&BVleft);
    setAABB(&BVright);
	
	*tree=pNode;
    pNode->BV = BV;

    printf("Bouncing Box\n");
    printAABB(pNode->BV);

 //   printf("Address   %d %d\n",&pNode->BV,&BV);
	pNode->numObject = numObjects;
	pNode->object = &objects[0];
	if (numObjects<=MIN_OBJECTS_PER_LEAF) {
		pNode->type = LEAF;
		pNode->left=NULL;
		pNode->right=NULL;
		printf("stop as leaf\n");
	}	else {
		pNode->type=NODE;

		int k= partitionObjectsTri(TriangleData,&objects[0], &tobjects[0], numObjects, BV, &BVleft, &BVright);
		//printAABB(BVleft);
		//printAABB(BVright);
		printf("Partition at %d\n",k);
		buildBVTreeTri( TriangleData, &(pNode->left), &objects[0], &tobjects[0], k, BVleft,debug);
		buildBVTreeTri( TriangleData, &(pNode->right), &objects[k], &tobjects[k], numObjects-k, BVright,debug);
	}
	
} 


void freeTree(Node *a)
{
	if (a->left!= NULL)
	  freeTree(a->left);
	if (a->right!= NULL)
	  freeTree(a->right);
	free(a);
}
void printTree(Node *a)
{
	printf("k\n");
	printAABB(a->BV);
	if (a->left!= NULL)
	  printTree(a->left);
	if (a->right!= NULL)
	  printTree(a->right);
}
