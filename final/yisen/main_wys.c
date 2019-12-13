#include "inputoutput.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bouncingBoxTree.c"
#include "bouncingBoxTree.h"
#include "BVTreeTraversal.c"
#include "BVTreeTraversal.h"

int main(int argc, char *argv[]) {
	const char s1[20]={"mesh.csv"};
	const char s2[20]={"sphere.csv"}; 
	const char s3[20]={"out.csv"}; 
	int mesh_num=0, sphere_num=0, i, j, k;
	FILE *f1, *f2, *f3;
	f1 = fopen(s1, "r");
	f2 = fopen(s2, "r");
	f3 = fopen(s3, "w");
	double *mesh_data=ReadCSV(f1,&mesh_num,3,3);
	double radius;
	double *sphere_data=ReadCSV2(f2,&radius,&sphere_num,3);
	int objects1[30000],tobjects1[30000],objects2[30000],tobjects2[30000];
	for (i=0;i<mesh_num;i++) {
		objects1[i]=i;
	}
    for (i=0;i<sphere_num;i++) {
			objects2[i]=i;	    
	}
	Node *treeTri,*treeSph;
	AABB BV0,BV1;
    setAABB(&BV0);
    setAABB(&BV1);
	for (i=0;i<mesh_num;i++)
	{
		updateBouncingBoxTri(mesh_data,i,&BV0);
	}
	for (i=0;i<sphere_num;i++) {
		updateBouncingBoxSph(sphere_data,i,&BV1);
	}
	printf("Start building tree---------------------------------------------\n");
	printAABB(BV0);
	buildBVTreeTri(mesh_data,&treeTri,objects1,tobjects1,mesh_num,BV0,objects1);
	printf("Triangle tree finished---------------------------------------------\n");
	printAABB(BV1);
	buildBVTreeSph(sphere_data,&treeSph,objects2,tobjects2,sphere_num,BV1,objects2);
	printf("Sphere tree finished------------------------------------------------\n");
	
	
	printf("RootType %d %d\n",treeTri->type,treeSph->type);
	CollisionResult *list;
	BVTreeTraversal(list,treeTri,treeSph);

    double boxes[100];
	int len_box=0;
	getBox(treeTri,3,boxes,&len_box);
	printf("length of box list %d\n",len_box);
    WriteCSV(f3,boxes,len_box/6,6);
	if (mesh_data!=NULL) 	free(mesh_data);
	if (sphere_data!=NULL) 	free(sphere_data);
	freeTree(treeTri);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    return 0;
}

