//
//  inputoutput.c
//  hw_scv
//
//  Created by xinyi on 11/3/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//


#include "inputoutput.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double *ReadCSV(const char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "failed to open file for reading\n");
        exit(1);
    }
    char *line,*record;
    char buffer[1024];
    double value;
    int n=0;
    while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL) {
        n+=1;
    }
    fclose(fp);
    // put values in csv file into array A
    int m=(n-n/4)*3+n/4;
    double *A;
    A=(double*)malloc(m*sizeof(double));
    fp = fopen(filename, "r");
    int i=0;
    while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL) {
        record = strtok(line, ",");
        while (record != NULL){
            value = atof(record);
            A[i]=value;
            record= strtok(NULL,",");
            i+=1;
        }
        
    }
    fclose(fp);
    return A;
}

int Getlen(const char *filename){
    FILE *fp;
    fp = fopen(filename, "r");
    char *line;
    char buffer[1024];
    int n=0;
    while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL) {
        n+=1;
    }
    fclose(fp);
    return n;
}


double *GetboxSmin(double *center,double r,int lenS){
    //box for spheres
    double *boxSmin; //store boxS's min apex data
    boxSmin=(double *)malloc(lenS*sizeof(double));
    for(int i=0;i<lenS;i++){
        boxSmin[i]=center[i]-r;
    }
    return boxSmin;
}

double *GetboxSmax(double *center,double r,int lenS){
    //box for spheres
    double *boxSmax; //store boxS's min apex data
    boxSmax=(double *)malloc(lenS*sizeof(double));
    for(int i=0;i<lenS;i++){
        boxSmax[i]=center[i]+r;
    }
    return boxSmax;
}

double *Getplane(double *Apex,int lenT){ //the number of apexs is len*3/4，number of triangles is lenT/4
    double *plane,*a,*b,*c,*d;
    plane=(double*)malloc(lenT*4/3*sizeof(double));
    a=(double*)malloc(lenT/4*sizeof(double));
    b=(double*)malloc(lenT/4*sizeof(double));
    c=(double*)malloc(lenT/4*sizeof(double));
    d=(double*)malloc(lenT/4*sizeof(double));
    //loop based on the number of triangles
    for (int i=0;i<lenT/4;i++){
        a[i]=(Apex[i*9+4]-Apex[i*9+1])*(Apex[i*9+8]-Apex[i*9+2])-(Apex[i*9+7]-Apex[i*9+1])*(Apex[i*9+5]-Apex[i*9+2]);
        b[i]=(Apex[i*9+5]-Apex[i*9+2])*(Apex[i*9+6]-Apex[i*9+0])-(Apex[i*9+8]-Apex[i*9+2])*(Apex[i*9+3]-Apex[i*9]);
        c[i]=(Apex[i*9+3]-Apex[i*9+0])*(Apex[i*9+7]-Apex[i*9+1])-(Apex[i*9+6]-Apex[i*9+0])*(Apex[i*9+4]-Apex[i*9+1]);
        d[i]=-a[i]*Apex[i*9+0]-b[i]*Apex[i*9+1]-c[i]*Apex[i*9+2];
    }
    int step=0;
    for (int i=0;i<lenT/4;i++){
        plane[i*4]=a[step];
        plane[i*4+1]=b[step];
        plane[i*4+2]=c[step];
        plane[i*4+3]=d[step];
        step+=1;
    }
    return plane;
}

double *CenterToP(double *center,double *plane,int lenT,int lens){
    double *centerP;
    centerP=(double*)malloc(lens*lenT/4*sizeof(double));
    int step=0;
    for(int i=0;i<lens/3;i++){
        for(int j=0;j<lenT/4;j++){
            centerP[step]=center[i*3]-plane[j*4]*(plane[j*4]*center[i*3]+plane[j*4+1]*center[i*3+1]+plane[j*4+2]*center[i*3+2]+plane[j*4+3])/(plane[j*4]*plane[j*4]+plane[j*4+1]*plane[j*4+1]+plane[j*4+2]*plane[j*4+2]);
            centerP[step+1]=center[i*3+1]-plane[j*4+1]*(plane[j*4]*center[i*3]+plane[j*4+1]*center[i*3+1]+plane[j*4+2]*center[i*3+2]+plane[j*4+3])/(plane[j*4]*plane[j*4]+plane[j*4+1]*plane[j*4+1]+plane[j*4+2]*plane[j*4+2]);
            centerP[step+2]=center[i*3+2]-plane[j*4+2]*(plane[j*4]*center[i*3]+plane[j*4+1]*center[i*3+1]+plane[j*4+2]*center[i*3+2]+plane[j*4+3])/(plane[j*4]*plane[j*4]+plane[j*4+1]*plane[j*4+1]+plane[j*4+2]*plane[j*4+2]);
            step+=3;
        }
    }
    return centerP;
}







int colli(double *Apex,int *ID, double *center,int *IDs){
    

    
    return 0;
}

