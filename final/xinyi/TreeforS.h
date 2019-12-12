//
//  TreeforS.h
//  459FinalProject
//
//  Created by xinyi on 12/1/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#ifndef TreeforS_h
#define TreeforS_h

#include <stdio.h>
///min point first 
///get the max and min point of box for spheres
double *getboxS(const char *filenameS);

///box1min:x,y are min of old box,z is z of center
///box1max:x,y are center, z is max of old box
double* nextBoxS1(double *boxS,int r);

///box2min:x,z are center,y is old box
///box2max:x,z are old box, y is center
double* nextBoxS2(double *boxS,int r);

///box3min:center
///box3max:box
double* nextBoxS3(double *boxS,int r);

///box4min:y,z are center,x is old box
///box4max:y,z are old box, x is center
double* nextBoxS4(double *boxS,int r);

///box5min:old box
///box5max:center
double* nextBoxS5(double *boxS,int r);

///box6min:x is center,y,z are old box
///box6max:x is old box, y,z zre center
double* nextBoxS6(double *boxS,int r);

///box7min:x,y is center,z are old box
///box7max:x,y is old box, z zre center
double* nextBoxS7(double *boxS,int r);

///box8min:y is center,x,z are old box
///box8max:y is old box, x,z zre center
double* nextBoxS8(double *boxS,int r);

///determing if the space is a box
int IsBox(double *box);
#endif /* TreeforS_h */
