//
//  getCond.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getCond.h"
#include "getData.h"
#include "getNum.h"

double *Getplane(const char *filename){ //the number of apexs is len*3/4，number of triangles is lenT/4
    double *Apex=getApex(filename);
    int lenT=getT(filename)*4;
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

double *CenterToP(const char *filenameT,const char *filenameS){
    double *center=getCenter(filenameS);
    double *plane=Getplane(filenameT);
    int lenT=getT(filenameT)*4;
    int lens=getS(filenameS)*3;
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


