//
//  TreeforS.c
//  459FinalProject
//
//  Created by xinyi on 12/1/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//
#include "getCond.h"
#include "getData.h"
#include "getNum.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TreeforS.h"


double *getboxS(const char *filenameS){
    double *S = ReadCSV(filenameS);
    int r = S[3];
    double *center = getCenter(filenameS);
    int numS = getS(filenameS);
    
    //find max x,y,z
    double max_x=center[0];
    for (int i=0;i<numS*3;i+=3){
        if(max_x<=center[i]){
            max_x=center[i];
        }
    }
    double max_y=center[1];
    for (int i=1;i<numS*3;i+=3){
        if(max_y<=center[i]){
            max_y=center[i];
        }
    }
    double max_z=center[2];
    for (int i=2;i<numS*3;i+=3){
        if(max_z<=center[i]){
            max_z=center[i];
        }
    }
    double maxS[3]={max_x+r,max_y+r,max_z+r};
    //find min x,y,z
    double min_x=center[0];
    for (int i=0;i<numS*3;i+=3){
        if(min_x>=center[i]){
            min_x=center[i];
        }
    }
    double min_y=center[1];
    for (int i=0;i<numS*3;i+=3){
        if(min_y>=center[i]){
            min_y=center[i];
        }
    }
    double min_z=center[2];
    for (int i=0;i<numS*3;i+=3){
        if(min_z>=center[i]){
            min_z=center[i];
        }
    }
    double minS[3]={min_x-r,min_y-r,min_z-r};
    double *boxS;
    boxS=(double*)malloc(6*sizeof(double));
    int index=0;
    for(int i=0;i<3;i++){
        boxS[index]=minS[i];
        index++;
    }
    for(int i=0;i<3;i++){
        boxS[index]=maxS[i];
        index++;
    }
    
    return boxS;
}

///box1min:x,y are min of old box,z is z of center
///box1max:x,y are center, z is max of old box
double* nextBoxS1(double *boxS){
    ///get center of the old box
    double Box_center[3]={(boxS[3]-boxS[0])/2,(boxS[4]-boxS[1])/2,(boxS[5]-boxS[2])/2};
    double *nextBoxS1;
    nextBoxS1=(double*)malloc(6*sizeof(double));
    //find max x,y,z
    nextBoxS1[0]=boxS[0];
    nextBoxS1[1]=boxS[1];
    nextBoxS1[2]=Box_center[2];
    nextBoxS1[3]=Box_center[0];
    nextBoxS1[4]=Box_center[1];
    nextBoxS1[5]=boxS[5];
    return nextBoxS1;
}
///box2min:x,z are center,y is old box
///box2max:x,z are old box, y is center
double* nextBoxS2(double *boxS){
    ///get center of the old box
    double Box_center[3]={(boxS[3]-boxS[0])/2,(boxS[4]-boxS[1])/2,(boxS[5]-boxS[2])/2};
    double *nextBoxS2;
    nextBoxS2=(double*)malloc(6*sizeof(double));
    //find max x,y,z
    nextBoxS2[0]=Box_center[0];
    nextBoxS2[1]=boxS[1];
    nextBoxS2[2]=Box_center[2];
    nextBoxS2[3]=boxS[3];
    nextBoxS2[4]=Box_center[1];
    nextBoxS2[5]=boxS[5];
    return nextBoxS2;
}

///box3min:center
///box3max:box
double* nextBoxS3(double *boxS){
    ///get center of the old box
    double Box_center[3]={(boxS[3]-boxS[0])/2,(boxS[4]-boxS[1])/2,(boxS[5]-boxS[2])/2};
    double *nextBoxS3;
    nextBoxS3=(double*)malloc(6*sizeof(double));
    int index=0;
    for(int i=0;i<3;i++){
        nextBoxS3[index]=Box_center[i];
        index++;
    }
    for(int i=3;i<6;i++){
        nextBoxS3[index]=boxS[i];
        index++;
    }
    return nextBoxS3;
}

///box4min:y,z are center,x is old box
///box4max:y,z are old box, x is center
double* nextBoxS4(double *boxS){
    ///get center of the old box
    double Box_center[3]={(boxS[3]-boxS[0])/2,(boxS[4]-boxS[1])/2,(boxS[5]-boxS[2])/2};
    double *nextBoxS4;
    nextBoxS4=(double*)malloc(6*sizeof(double));
    //find max x,y,z
    nextBoxS4[0]=boxS[0];
    nextBoxS4[1]=Box_center[1];
    nextBoxS4[2]=Box_center[2];
    nextBoxS4[3]=Box_center[0];
    nextBoxS4[4]=boxS[4];
    nextBoxS4[5]=boxS[5];
    return nextBoxS4;
}

///box5min:old box
///box5max:center
double* nextBoxS5(double *boxS){
    ///get center of the old box
    double Box_center[3]={(boxS[3]-boxS[0])/2,(boxS[4]-boxS[1])/2,(boxS[5]-boxS[2])/2};
    double *nextBoxS5;
    nextBoxS5=(double*)malloc(6*sizeof(double));
    int index=0;
    for(int i=0;i<3;i++){
        nextBoxS5[index]=boxS[i];
        index++;
    }
    for(int i=0;i<3;i++){
        nextBoxS5[index]=Box_center[i];
        index++;
    }
    return nextBoxS5;
}

///box6min:x is center,y,z are old box
///box6max:x is old box, y,z zre center
double* nextBoxS6(double *boxS){
    ///get center of the old box
    double Box_center[3]={(boxS[3]-boxS[0])/2,(boxS[4]-boxS[1])/2,(boxS[5]-boxS[2])/2};
    double *nextBoxS6;
    nextBoxS6=(double*)malloc(6*sizeof(double));
    //find max x,y,z
    nextBoxS6[0]=Box_center[0];
    nextBoxS6[1]=boxS[1];
    nextBoxS6[2]=boxS[2];
    nextBoxS6[3]=boxS[3];
    nextBoxS6[4]=Box_center[1];
    nextBoxS6[5]=Box_center[2];
    return nextBoxS6;
}

///box7min:x,y is center,z are old box
///box7max:x,y is old box, z zre center
double* nextBoxS7(double *boxS){
    ///get center of the old box
    double Box_center[3]={(boxS[3]-boxS[0])/2,(boxS[4]-boxS[1])/2,(boxS[5]-boxS[2])/2};
    double *nextBoxS7;
    nextBoxS7=(double*)malloc(6*sizeof(double));
    //find max x,y,z
    nextBoxS7[0]=Box_center[0];
    nextBoxS7[1]=Box_center[1];
    nextBoxS7[2]=boxS[2];
    nextBoxS7[3]=boxS[3];
    nextBoxS7[4]=boxS[4];
    nextBoxS7[5]=Box_center[2];
    return nextBoxS7;
}

///box8min:y is center,x,z are old box
///box8max:y is old box, x,z zre center
double* nextBoxS8(double *boxS){
    ///get center of the old box
    double Box_center[3]={(boxS[3]-boxS[0])/2,(boxS[4]-boxS[1])/2,(boxS[5]-boxS[2])/2};
    double *nextBoxS8;
    nextBoxS8=(double*)malloc(6*sizeof(double));
    //find max x,y,z
    nextBoxS8[0]=boxS[0];
    nextBoxS8[1]=Box_center[1];
    nextBoxS8[2]=boxS[2];
    nextBoxS8[3]=Box_center[0];
    nextBoxS8[4]=boxS[4];
    nextBoxS8[5]=Box_center[2];
    return nextBoxS8;
}
