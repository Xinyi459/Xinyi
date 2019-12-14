///Yisen Wang
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include  <limits.h>
#include "bouncingBoxTree.h"


void printAABB(AABB a)
{
/**
 * Debug implementation: print bouncing box \n 
 */
	printf("printAABB\n");
	int i;
	for (i=0;i<3;i++)
	  printf("%f %f\n",a.min[i],a.max[i]);
}

void setAABB(AABB *a)
{
/**
 * Bouncing Box implementation: set BV to zero \n 
 */
	int i;
	for (i=0;i<3;i++) {
	    a->min[i]=0;
		a->max[i]=0;
	}

}
void printArr(int *a,int n)
{
/**
 *Debug implementation: print objects list that contain all objects in this node \n 
 */
	int i;
	for (i=0;i<n;i++)
	  printf("%d ",a[i]);
	printf("\n");
}
//***************************************************************************************
//
//! \brief  BV Tree implementation: find axis that has largest length
//!
//! \param  [in] number is the data you want to print.
//! \retval index of the axis: 0 - x axis \n 
//!                            1 - y axis \n 
//!                           2 - z axis \n 
//!
//
//***************************************************************************************
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
//***************************************************************************************
//
//! \brief  Bouncing Box implementation: chech whether two bouncing box intersect by checking the projections onto 3 axis
//! \retval if two AABB are intersected: 0-interescted
//!
//
//***************************************************************************************
int TestAABB(AABB a,AABB b)
{
	if (a.max[0] < b.min[0] || a.min[0] > b.max[0]) return 1;
	if (a.max[1] < b.min[1] || a.min[1] > b.max[1]) return 1;
	if (a.max[2] < b.min[2] || a.min[2] > b.max[2]) return 1;
	return 0;
}
//***************************************************************************************
//
//! \brief  BV Tree implementation: find child with least number of object to put new object \n 
//! \retval 0-left node, 1-right node \n 
//!
//
//***************************************************************************************
int findNodeToPut(float mean, float minCoordinate,float maxCoordinate, int num1, int num2)
{
	if (maxCoordinate <= mean ) return LEFT;
	if (minCoordinate >= mean ) return RIGHT;
	if (maxCoordinate > mean && minCoordinate < mean)
	  if (num1>=num2) { return RIGHT; }
	  else { return LEFT; }
}
//***************************************************************************************
//
//! \brief  BV Tree implementation(Triangle): update bouncing box with a new triangle 
//!
//
//***************************************************************************************
void updateBouncingBoxTri(double *TriangleData,int index,AABB *pBV)
{
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
//***************************************************************************************
//
//! \brief  BV Tree implementation(Triangle): divide objects into 2 node by its position on the longest axis \n 
//!                                update the boucing box for two nodes at the same time \n  
//!
//
//***************************************************************************************
int partitionObjectsTri(double *TriangleData,
                        int *objects, int *tobjects,
						int numObjects, 
						AABB BV, 
						AABB *pBVleft, 
						AABB *pBVright)
{
	int index=maxIndex(fabs(BV.max[0]-BV.min[0]),
	              fabs(BV.max[1]-BV.min[1]),
	              fabs(BV.max[2]-BV.min[2])
	);
	//printf("Partition index= %d\n",index); 
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
//***************************************************************************************
//
//! \brief  BV Tree implementation(Triangle): main function for build BV tree \n 
//!
//! \param  [TriangleData] pointer to data of triangle mesh
//! \param  [tree] pointer to Node
//! \param  [objects] list of objects contained in the node 
//! \param  [tobjects] extra list for dividing the node
//! \param  [BV] bouncing box that contain all objects in this node \n 
//
//***************************************************************************************
void buildBVTreeTri(double *TriangleData, 
                    Node **tree, 
					int *objects, int *tobjects, 
					int numObjects, AABB BV,int *debug)
{
	Node *pNode=(Node*)malloc(sizeof(Node));
    AABB BVleft, BVright;
    setAABB(&BVleft);
    setAABB(&BVright);
	
	*tree=pNode;
    pNode->BV = BV;

	pNode->numObject = numObjects;
	pNode->object = &objects[0];
	if (numObjects<=MIN_OBJECTS_PER_LEAF) {
		pNode->type = LEAF;
		pNode->left=NULL;
		pNode->right=NULL;
		updateBouncingBoxTri(TriangleData,pNode->object[0],&pNode->BV);
	}	else {
		pNode->type=NODE;

		int k= partitionObjectsTri(TriangleData,&objects[0], &tobjects[0], numObjects, BV, &BVleft, &BVright);
		buildBVTreeTri( TriangleData, &(pNode->left), &objects[0], &tobjects[0], k, BVleft,debug);
		buildBVTreeTri( TriangleData, &(pNode->right), &objects[k], &tobjects[k], numObjects-k, BVright,debug);
	}
	
} 
//***************************************************************************************
//
//! \brief  BV Tree implementation(Sphere): update bouncing box with a new sphere \n  
//!
//
//***************************************************************************************
void updateBouncingBoxSph(double *SphereData,int index,AABB *pBV)
{
    double r=SphereData[index*4+3];
	if (pBV->max[0]-pBV->min[0] < MIN_SIZE &&
	   pBV->max[1]-pBV->min[1]  < MIN_SIZE && 
	   pBV->max[2]-pBV->min[2]  < MIN_SIZE) {
	   	
	    for (size_t i=0; i<3; i++) {
	    pBV->min[i]=SphereData[index*4+i]-r;
	    pBV->max[i]=SphereData[index*4+i]+r;
	    }
	    for (size_t i=0; i<3; i++)
	      if ( pBV->max[i]-pBV->max[i]<MIN_SIZE) {
	        pBV->min[i] -= MIN_SIZE;	
	        pBV->max[i] += MIN_SIZE;
		    }
	} else {
        for (size_t i=0; i<3; i++) {
		  pBV->min[i]=min(pBV->min[i],SphereData[index*4+i]-r,INT_MAX);
		  pBV->max[i]=max(pBV->max[i],SphereData[index*4+i]+r,INT_MIN);
	    }
	}
}
//***************************************************************************************
//
//! \brief  BV Tree implementation(Sphere): divide objects into 2 node by its position on the longest axis \n 
//!                              update the boucing box for two nodes at the same time \n  
//!
//
//***************************************************************************************
int partitionObjectsSph(double *SphereData,
                        int *objects, int *tobjects,
						int numObjects, 
						AABB BV, 
						AABB *pBVleft, 
						AABB *pBVright)
{
	int index=maxIndex(fabs(BV.max[0]-BV.min[0]),
	              fabs(BV.max[1]-BV.min[1]),
	              fabs(BV.max[2]-BV.min[2])	);
	double r=SphereData[3];
	//printAABB(BV);
	//printf("Partition index= %d\n",index); 
	int i, j, k, x, y, t;
	double mean=0;
	for (i=0;i<numObjects;i++) {
	    mean += SphereData[objects[i]*4+index];
	}
	mean /= numObjects;
	//printf("mean %f\n",mean);
	x=0;y=numObjects-1;
	for (i=0; i<numObjects; i++)
	{
		double maxCoordinate =SphereData[objects[i]*4+index]+r;
		double minCoordinate = SphereData[objects[i]*4+index]-r;
		
		int r=findNodeToPut(mean, minCoordinate,maxCoordinate, x+1, numObjects-y);
		
		if (r==LEFT ) {
			// put into left node
			tobjects[x++] = objects[i];
			updateBouncingBoxSph(SphereData,objects[i], pBVleft);
		} else
		if (r==RIGHT) {
			// put into right node
			tobjects[y--] = objects[i];
			updateBouncingBoxSph(SphereData,objects[i], pBVright); 
		}
	}
	for (i=0; i<numObjects; i++)
	objects[i]=tobjects[i];
	return(x);
}
//***************************************************************************************
//
//! \brief  BV Tree implementation(Sphere): main function for build BV tree
//!
//! \param  [SphereData] pointer to data of triangle mesh
//! \param  [tree] pointer to Node
//! \param  [objects] list of objects contained in the node 
//! \param  [tobjects] extra list for dividing the list
//! \param  [BV] bouncing box that contain all objects in this node \n 
//
//***************************************************************************************
void buildBVTreeSph(double *SphereData, 
                    Node **tree, 
					int *objects, int *tobjects, 
					int numObjects, AABB BV,int *debug)
{
	Node *pNode=(Node*)malloc(sizeof(Node));
    AABB BVleft, BVright;
    setAABB(&BVleft);
    setAABB(&BVright);
	*tree=pNode;
    pNode->BV = BV;
    //printf("Bouncing Box\n");
    //printAABB(pNode->BV);

 //   printf("Address   %d %d\n",&pNode->BV,&BV);
	pNode->numObject = numObjects;
	pNode->object = &objects[0];
	if (numObjects<=MIN_OBJECTS_PER_LEAF) {
		pNode->type = LEAF;
		pNode->left=NULL;
		pNode->right=NULL;
	//	printf("look\n");
	//	printAABB(pNode->BV);
		//printf("stop as leaf\n");
	}	else {
		pNode->type=NODE;
		int k= partitionObjectsSph(SphereData,&objects[0], &tobjects[0], numObjects, BV, &BVleft, &BVright);
		//printAABB(BVleft);
		//printAABB(BVright);
	//	printf("Partition at %d\n",k);
		buildBVTreeSph( SphereData, &(pNode->left), &objects[0], &tobjects[0], k, BVleft,debug);
		buildBVTreeSph( SphereData, &(pNode->right), &objects[k], &tobjects[k], numObjects-k, BVright,debug);
	}
	
} 


void freeTree(Node *a)
{
/**
 *BV Tree implementation: Free tree recursively
 */
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
