#ifndef bouncingBoxTree_H
#define bouncingBoxTree_H
#include <stdlib.h>
#include <stddef.h>

#define LEAF 0
#define NODE 11
#define LEFT 0
#define RIGHT 1
#define MIN_OBJECTS_PER_LEAF 1
#define MIN_SIZE 0.00001

/**
 * Definition of axis aligned bouncing box \n 
 * min point & max point \n 
 */
typedef struct  AABB_Def
{
	float min[3];  
	float max[3]; 
} AABB;

/**
 * Definition of triangle data \n 
 * data order is x1 y1 z1 x2 y2 z2 x3 y3 z3 \n 
 */
typedef struct Triangle_Def
{
  float p[9];
} Triangle;

/**
 * Definition of sphere data \n 
 * data order is x y z r \n 
 */
typedef struct Sphere_Def
{
	float p[4];
} Sphere;

/**
 * Struct of node for BV tree   \n
 * Node information: \n 
 * type: NODE/ LEAF  \n 
 * BV: bouncin box for objects of the node   \n 
 * numObject: number of objects in this node \n
 * object: pointer to an array that stored the index of objects belongs to this node \n
 */ 
typedef struct BVTreeNode
{
	int type;  ///node type
	AABB BV;   /// bouncing box
	int numObject;  ///number in node
	int *object;  ///index array to original data
	struct BVTreeNode *left; 
	struct BVTreeNode *right;  
} Node;


void printAABB(AABB a);
void setAABB(AABB *a);
void printArr(int *a,int n);
double maxIndex(double x, double y, double z);
double max(double x, double y, double z);
double min(float x, float y, float z);
int TestAABB(AABB a,AABB b);
int findNodeToPut(float mean, float minCoordinate,float maxCoordinate, int num1, int num2);
void updateBouncingBoxTri(double *TriangleData,int index,AABB *pBV);
int partitionObjectsTri(double *TriangleData,
                        int *objects, int *tobjects,
						int numObjects, 
						AABB BV, AABB *pBVleft, AABB *pBVright);
void buildBVTreeTri(double *TriangleData, 
                    Node **tree, 
					int *objects, int *tobjects, 
					int numObjects, AABB BV,int *debug);
void updateBouncingBoxSph(double *SphereData,int index,AABB *pBV);
int partitionObjectsSph(double *SphereData,
                        int *objects, int *tobjects,
						int numObjects, 
						AABB BV, 
						AABB *pBVleft, 
						AABB *pBVright);
void buildBVTreeSph(double *SphereData, 
                    Node **tree, 
					int *objects, int *tobjects, 
					int numObjects, AABB BV,int *debug);
void freeTree(Node *a);
void printTree(Node *a);
#endif
