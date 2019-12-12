#ifndef bouncingBoxTree_H
#define bouncingBoxTree_H
#include <stdlib.h>
#include <stddef.h>

#define LEAF 1
#define NODE 0
#define LEFT 0
#define RIGHT 1
#define MIN_OBJECTS_PER_LEAF 1
#define MIN_SIZE 0.0001

typedef struct Point_Def
{
  float p[3];
} Point;

typedef struct  AABB_Def
{
	float min[3];
	float max[3];
} AABB;

typedef struct Triangle_Def
{
  float p[9];
} Triangle;

typedef struct Sphere_Def
{
	Point center;
	float r;
} Sphere;

typedef struct BVTreeNode
{
	int type;
	AABB BV;
	int numObject;
	int *object;  //index array to original data
	struct BVTreeNode *left;
	struct BVTreeNode *right;  
} Node;
/*
int TestAABB(AABB a,AABB b);
int findNodeToPut(float mean, float mincoordinate,float maxcoordinate, int num1, int num2);
void updateBouncingBoxTri(int index, AABB *BV);
int partitionObjectsTri(int *objects, int *tobjects,  int numObjects, AABB BV, AABB *pBVleft, AABB *pBVright);
int buildBVTreeTri(Node **tree, int object[], int tobjects[], int numObjects, AABB BV);
*/
#endif
