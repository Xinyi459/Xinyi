//
//  getCond_new.c
//  459
//
//  Created by xinyi on 12/9/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "getCond.h"
#include "getData.h"
#include "getNum.h"
#include "getCond_new.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



double *GetplaneT(int pair[2],const char *filenameT){
    double *Apex = getApex(filenameT);
    //int numT = getT(filenameT);
    int idT=pair[1];
    double T[9];
    for(int i=0; i<9;i++){
        T[i]=Apex[idT*9+i];
    }
    double *plane;
    double a, b, c, d;
    plane = (double *)malloc(4 * sizeof(double));
    a  = (T[4] - T[1]) *
    (T[8] - T[ 2]) -
    (T[   7] - T[   1]) *
    (T[   5] - T[   2]);
    b  =
    (T[   5] - T[   2]) *
    (T[   6] - T[   0]) -
    (T[   8] - T[   2]) * (T[   3] - T[0 * 9]);
    c  = (T[   3] - T[   0]) *
    (T[   7] - T[   1]) -
    (T[   6] - T[   0]) *
    (T[   4] - T[   1]);
    d  = -a  * T[   0] - b  * T[   1] -
    c  * T[   2];
    plane[0]=a;
     plane[1]=b;
     plane[2]=c;
     plane[3]=d;
    
    return plane;
}

double*project(int pair[2],const char *filenameT,const char *filenameS){
    double *plane=GetplaneT(pair,filenameT);
    int idS=pair[0];
    double *centerP;
    double *S = getCenter(filenameS);
    double center[3];
    for(int i=0;i<3;i++){
        center[i]=S[idS*3+i];
    }
    centerP = (double *)malloc(3 * sizeof(double));
    centerP[0] =center[  0] -plane[0] *
    (plane[0] * center[  0] +
     plane[ 1] * center[  1] +
     plane[ 2] * center[  2] + plane[ 3]) /
    (plane[0] * plane[0] +
     plane[ 1] * plane[ 1] +
     plane[ 2] * plane[ 2]);
    centerP[ 1] =
    center[  1] -
    plane[ 1] *
    (plane[0] * center[  0] +
     plane[ 1] * center[  1] +
     plane[ 2] * center[  2] + plane[ 3]) /
    (plane[0] * plane[0] +
     plane[ 1] * plane[ 1] +
     plane[ 2] * plane[ 2]);
    centerP[2] =
    center[2] -
    plane[ 2] *
    (plane[0] * center[  0] +
     plane[ 1] * center[  1] +
     plane[ 2] * center[  2] + plane[ 3]) /
    (plane[0] * plane[0] +
     plane[ 1] * plane[ 1] +
     plane[ 2] * plane[ 2]);

    for(int i=0;i<3;i++){
        printf("%f ",centerP[i]);
    }
    return centerP;
}

double *CrossMatrix(double *vect) {
    double *C;
    C = (double *)malloc(9 * sizeof(double));
    C[0] = 0;
    C[1] = -vect[2];
    C[2] = vect[1];
    C[3] = vect[2];
    C[4] = 0;
    C[5] = -vect[0];
    C[6] = -vect[1];
    C[7] = vect[0];
    C[8] = 0;
    return C;
}

int colli(int pair[2],const char *filenameT,const char *filenameS){
    double *Apex = getApex(filenameT);
    double *S = getCenter(filenameS);
    double T[9];
    for(int i=0; i<9;i++){
        T[i]=Apex[pair[1]*9+i];
    }
    double center[3];
    for(int i=0;i<3;i++){
        center[i]=S[pair[0]*3+i];
    }
    double *centerP=project(pair,filenameT,filenameS);
    // get cross product
    double *C; // the cross matrix PA
    double *anotherC;//CA
    C = (double *)malloc(9 * sizeof(double));
    anotherC = (double *)malloc(9 * sizeof(double));
    
    double *vect;
    vect = (double *)malloc(3 * sizeof(double));
    double *refvect;
    refvect = (double *)malloc(3 * sizeof(double));
    double *anotherLine;
    anotherLine = (double *)malloc(3 * sizeof(double));
    // store cos from dot product
    double *Dot;
    Dot = (double *)malloc(3 * sizeof(double));
    //x
    vect[0] = centerP[0] - T[0]; //PA
    refvect[0] = T[0] -T[3]; // the line used for cross product AB
    anotherLine[0] =T[6] - T[0];//CA
    //y
    vect[1] = centerP[1] - T[1];
    refvect[1] = T[1] -T[4];
    anotherLine[1] =T[7] - T[1];
    //z
    vect[2] = centerP[2] - T[2];
    refvect[2] = T[2] -T[5];
    anotherLine[2] =T[8] - T[2];
    //get crossporduct
    //PA x AB CA x AB
    C=CrossMatrix(vect);
    anotherC=CrossMatrix(anotherLine);
    double c[3];
    double anotherc[3];
    for(int i=0;i<3;i++){
        c[i]=C[i*3+0]*refvect[0]+C[i*3+1]*refvect[1]+C[i*3+2]*refvect[2];
        anotherc[i]=anotherC[i*3+0]*refvect[0]+anotherC[i*3+1]*refvect[1]+anotherC[i*3+2]*refvect[2];
    }
    for(int i=0;i<3;i++){
        Dot[0]+=c[i]*anotherc[i];
    }
    
    //x
    vect[0] = centerP[0] - T[3]; //PB
    refvect[0] = T[3] -T[6]; // the line used for cross product BC
    anotherLine[0] =T[0] - T[3];//AB
    //y
    vect[1] = centerP[1] - T[4];
    refvect[1] = T[4] -T[7];
    anotherLine[1] =T[1] - T[4];
    //z
    vect[2] = centerP[2] - T[5];
    refvect[2] = T[5] -T[8];
    anotherLine[2] =T[2] - T[5];
    //get crossporduct
    
    C=CrossMatrix(vect);
    anotherC=CrossMatrix(anotherLine);
    for(int i=0;i<3;i++){
        c[i]=C[i*3+0]*refvect[0]+C[i*3+1]*refvect[1]+C[i*3+2]*refvect[2];
        anotherc[i]=anotherC[i*3+0]*refvect[0]+anotherC[i*3+1]*refvect[1]+anotherC[i*3+2]*refvect[2];
    }
    for(int i=0;i<3;i++){
        Dot[1]+=c[i]*anotherc[i];
    }

    //x
    vect[0] = centerP[0] - T[6]; //PC
    refvect[0] = T[6] -T[0]; // the line used for cross product CA
    anotherLine[0] =T[3] - T[6];//BC
    //y
    vect[1] = centerP[1] - T[7];
    refvect[1] = T[7] -T[1];
    anotherLine[1] =T[4] - T[7];
    //z
    vect[2] = centerP[2] - T[8];
    refvect[2] = T[8] -T[2];
    anotherLine[2] =T[5] - T[8];
    //get crossporduct
    
    C=CrossMatrix(vect);
    anotherC=CrossMatrix(anotherLine);
    for(int i=0;i<3;i++){
        c[i]=C[i*3+0]*refvect[0]+C[i*3+1]*refvect[1]+C[i*3+2]*refvect[2];
        anotherc[i]=anotherC[i*3+0]*refvect[0]+anotherC[i*3+1]*refvect[1]+anotherC[i*3+2]*refvect[2];
    }
    for(int i=0;i<3;i++){
        Dot[2]+=c[i]*anotherc[i];
    }
    
    //in or out
    int flag=1; //in the triangle
    for(int i=0;i<3;i++){
        if (Dot[i]>0){
            continue;
        }
        else{
            flag=0;
            break;
        }
    }
    //collision or not 1 means collision
    int r = S[3];
    int colli=1;
    double dist=0;
    double line1[3],line2[3];
    if(flag==1){
        for(int i=0;i<3;i++){
            dist+=(center[i]-centerP[i])*(center[i]-centerP[i]);
        }
        dist=sqrt(dist);
        if(dist>r){
            colli=0;
            dist=0;
        }
        dist=0;
    }
    else{
        for(int i=0;i<3;i++){
            line1[i]=center[i]-T[i]; //PA
            line2[i]=T[3+i]-T[i];//BA
        }
        
        for(int i=0;i<3;i++){
            dist+=line1[i]*line2[2];
        }
        dist=dist/sqrt(line2[0]*line2[0]+line2[1]*line2[1]+line2[2]*line2[2]);
        if(dist<=r){
            colli=1;
        }
        for(int i=0;i<3;i++){
            line1[i]=center[i]-T[3+i]; //PB
            line2[i]=T[6+i]-T[3+i];//CB
        }
        for(int i=0;i<3;i++){
            dist+=line1[i]*line2[2];
        }
        dist=dist/sqrt(line2[0]*line2[0]+line2[1]*line2[1]+line2[2]*line2[2]);
        if(dist<=r){
            colli=1;
        }
        for(int i=0;i<3;i++){
            line1[i]=center[i]-T[6+i]; //PC
            line2[i]=T[i]-T[6+i];//AC
        }
        
        for(int i=0;i<3;i++){
            dist+=line1[i]*line2[2];
        }
        dist=dist/sqrt(line2[0]*line2[0]+line2[1]*line2[1]+line2[2]*line2[2]);
        if(dist<=r){
            colli=1;
        }
    }
    return colli;
}


