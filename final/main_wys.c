#include "inputoutput.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bouncingBoxTree.c"
#include "bouncingBoxTree.h"

int main(int argc, char *argv[]) {
	const char s1[20]={"bunny_mesh2.csv"};
	int mesh_num=0, i, j, k;
	FILE *f1;
	f1 = fopen(s1, "r");
	double *mesh_data=ReadCSV(f1,&mesh_num,3,3);
	int objects[30000],tobjects[30000];
	for (i=0;i<mesh_num;i++)
	    objects[i]=i;
	Node *treeTri;
	AABB BV0,a;
    setAABB(&BV0);
    a=BV0;
	for (i=0;i<mesh_num;i++)
	{
		updateBouncingBoxTri(mesh_data,i,&BV0);
	}
	//printAABB(BV0);
	printf("Start building tree---------------------------------------------\n");
	buildBVTreeTri(mesh_data,&treeTri,objects,tobjects,mesh_num,BV0,objects);
	printf("Building finished------------------------------------------------\n");
	//printTree(treeTri);
	if (mesh_data!=NULL)
	free(mesh_data);
	freeTree(treeTri);
    fclose(f1);
    return 0;
}

