#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include "bouncingBoxTree.h"

Triangle * TriangleData;
int maxIndex(float x, float y, float z)
{
	if (x>=y && x>=z ) return 0;
	if (y>=x && y>=z ) return 1;
	if (z>=x && z>=y ) return 2;
}

int max(float x, float y, float z)
{
	if (x>=y && x>=z ) return x;
	if (y>=x && y>=z ) return y;
	if (z>=x && z>=y ) return z;
}

int min(float x, float y, float z)
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

void updateBouncingBoxTri(int index,AABB *BV)
{
	if (BV->max[0]-BV->min[0] == 0 &&
	   BV->max[1]-BV->min[1] == 0 && 
	   BV->max[1]-BV->min[1] == 0) {
	    for (size_t i=0; i<3; i++) {
	      BV->min[i]=min(TriangleData[index].p[i],
	               TriangleData[index].p[3+i],
				   TriangleData[index].p[6+i]);
	      BV->max[i]=max(TriangleData[index].p[i],
	               TriangleData[index].p[3+i],
				   TriangleData[index].p[6+i]);
	    }
	} else {
        for (size_t i=0; i<3; i++) {
	      float tmin=min(TriangleData[index].p[i],
	               TriangleData[index].p[3+i],
				   TriangleData[index].p[6+i]);
		  BV->min[i]=min(BV->min[i],tmin,INT_MIN);
	      float tmax=max(TriangleData[index].p[i],
	               TriangleData[index].p[3+i],
				   TriangleData[index].p[6+i]);
		  BV->max[i]=min(BV->max[i],tmax,INT_MAX);
	    }
	}
}

int partitionObjectsTri(int *objects, int *tobjects,  int numObjects, AABB BV, AABB *pBVleft, AABB *pBVright)
{
	int index=maxIndex(abs(BV.min[0]-BV.max[0]),
	              abs(BV.min[1]-BV.max[1]),
	              abs(BV.min[2]-BV.max[2])
	);
	size_t i, j, k, x, y, t;
	float mean=0;
	for (i=0;i<numObjects;i++) {
	    mean += TriangleData[objects[i]].p[index];
	    mean += TriangleData[objects[i]].p[3+index];
	    mean += TriangleData[objects[i]].p[6+index];
	}
	mean /= numObjects * 3;
	x=0;y=numObjects-1;
	for (i=0; i<numObjects; i++)
	{
		float maxCoordinate = max(TriangleData[objects[i]].p[index] , 
		                    TriangleData[objects[i]].p[3+index] , 
					        TriangleData[objects[i]].p[6+index]);
		float minCoordinate = min(TriangleData[objects[i]].p[index] , 
		                    TriangleData[objects[i]].p[3+index] , 
					        TriangleData[objects[i]].p[6+index]);
		
		int r=findNodeToPut(mean, minCoordinate,maxCoordinate, x, numObjects-y);
		
		if (r==LEFT ) {
			// put into left node
			tobjects[y--] = objects[i];
			updateBouncingBoxTri(objects[i], pBVleft);
		} else
		if (r==RIGHT) {
			// put into right node
			tobjects[x++] = objects[i];
			updateBouncingBoxTri(objects[i], pBVright); 
		}
	}
	for (i=0; i<numObjects; i++)
	objects[i]=tobjects[i];
}

int buildBVTreeTri(Node **tree, int objects[], int tobjects[], int numObjects, AABB BV)
{
	assert(numObjects>0);
	
	Node *pNode=(Node*)malloc(sizeof(Node));
	
    AABB BVleft, BVright;
	*tree=pNode;
	
//	pNode->BV = ComputeBV(&object[0],numObjects);
    pNode->BV = BV;
	
	if (numObjects<=MIN_OBJECTS_PER_LEAF) {
		pNode->type = LEAF;
		pNode->numObject = numObjects;
		pNode->object = &objects[0];
	}	else {
		pNode->type=NODE;
		int k= partitionObjectsTri(&objects[0], &tobjects[0], numObjects, BV, &BVleft, &BVright);
		buildBVTreeTri( &(pNode->left), &objects[0], &tobjects[0], k, BVleft);
		buildBVTreeTri( &(pNode->right), &objects[k], &tobjects[k], numObjects-k, BVright);
	}
	
} 

typedef struct testbit {
	unsigned int x:8;
	unsigned int y:8;
	unsigned int z:12;
} bitf;
int main(int argc, char *argv[])
{
	bitf a = {17,1,1};
	printf("%d\n",sizeof(struct testbit));
	bitf *p=&a;
	printf("%x\n",*((int *)p));
	return 0;
}
