//
//  main.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//



#include "getCond_new.h"
#include "getData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, const char *argv[]) {
    
    const char *filenameS =
    "sphere.csv";
    const char *filenameT =
    "triangle.csv";
    
    ///////////////first method////////////
    int*collis;
    double *S = ReadCSV(filenameS);
    int r = S[3];
    double *Apex = getApex(filenameT);
    double *center = getCenter(filenameS);
    double *A = ReadCSV(filenameT);
    int numT = A[0];
    double *B = ReadCSV(filenameS);
    int numS = B[4];
    collis=(int*)malloc(numT*numS*sizeof(int));
    double sphere_data[4]={r,r,r,r};
    double mesh_data[9];
    long int index=0;
    clock_t start = clock();
    for(int s=0;s<numS;s++){
        for(int i=0;i<3;i++){
            sphere_data[i]=center[s*3+i];
        }
        for(int m=0;m<numT;m++){
            for(int j=0;j<9;j++){
                mesh_data[j]=Apex[m*9+j];
            }
            int c=colli(mesh_data,sphere_data);
            collis[index]=c;
            index+=1;
        }
    }
    clock_t end = clock();
    double time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
    printf("the first method used time: %f\n", time);
    
    ///////////////output//////////////////////
    
    FILE *fp = NULL;
    fp = fopen("output.csv", "w");
    if (NULL == fp) {
        return -1;
    }
    fprintf(fp, "%s,%s\n", "s", "t");
    for (int i = 0; i < numS; i++) {
        for (int j = 0; j < numT; j++) {
            if (collis[i * numT + j] == 1) {
                fprintf(fp, "%d,%d\n", i, j);
            }
        }
    }
    fclose(fp);
    fp = NULL;
    free(collis);
   
    return 0;
}
