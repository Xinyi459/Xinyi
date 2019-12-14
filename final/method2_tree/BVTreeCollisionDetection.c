///Yisen Wang
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "bouncingBoxTree.h"
#include "BVTreeTraversal.h"
#include "inputData.h"
#include "getCond_new.h"

int main(int argc, char *argv[]) {
	const char s1[20]={"mesh.csv"};
	const char s2[20]={"sphere.csv"}; 
	const char s3[40]={"collision_detection.out"}; 
	int mesh_num=0, sphere_num=0, result_len=0, i, j, k;
	FILE *f1, *f2, *f3;
	f1 = fopen(s1, "r");
	f2 = fopen(s2, "r");
	f3 = fopen(s3, "w");
	double *mesh_data=ReadCSV1(f1,&mesh_num,3,3);
	double radius;
	double *sphere_data=ReadCSV2(f2,&radius,&sphere_num,3);
	int objects1[30000],tobjects1[30000],objects2[30000],tobjects2[30000];
	clock_t start_time = clock();
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
    /// Update bouncing box for root
	for (i=0;i<mesh_num;i++)
	{
		updateBouncingBoxTri(mesh_data,i,&BV0);
	}
	for (i=0;i<sphere_num;i++) {
		updateBouncingBoxSph(sphere_data,i,&BV1);
	}
	
	printf("Start building tree---------------------------------------------\n");
	//printAABB(BV0);
	buildBVTreeTri(mesh_data,&treeTri,objects1,tobjects1,mesh_num,BV0,objects1); ///generate BV tree for triangle mesh
	printf("Triangle tree finished---------------------------------------------\n");
	//printAABB(BV1);
	buildBVTreeSph(sphere_data,&treeSph,objects2,tobjects2,sphere_num,BV1,objects2); ///generate BV tree for sphere
	printf("Sphere tree finished------------------------------------------------\n");
	
	
	CollisionResult *list=(CollisionResult*)malloc(sizeof(CollisionResult));
	list->next=NULL;
	BVTreeTraversal(treeTri,treeSph,mesh_data, sphere_data, list, &result_len);    ///treversal two BV tree to get collision results
    clock_t end_time = clock();
    double time_tree = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
    

	printf("length of collision pair %d\ntime consume %f ms\n",result_len,time_tree);
    printList(f3,list,result_len,time_tree);
    
    int compare=0;
    if (compare) {
       start_time = clock();
      result_len=0;
      DirectTraversal(mesh_data, mesh_num, sphere_data, sphere_num, &result_len);
      end_time = clock();
      double time_direct = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;
      printf("Time consume for brute force %f ms\n",time_direct);
    }
    int debug=0;
    if (debug) {
    	double boxes[100];
        int len_box=0;
        getBox(treeTri,3,boxes,&len_box);
    	double a[9]={1,0,0,0,0.5,0,0,0,0};
    	double b[4]={3,0,0,0.5};
    	int res=colli(a,b);
    	printf("test %d",res);
    	
    }
	if (mesh_data!=NULL) 	free(mesh_data);
	if (sphere_data!=NULL) 	free(sphere_data);
	freeTree(treeTri);
    fclose(f1);
    fclose(f2);
    fclose(f3);
    

    return 0;
}


