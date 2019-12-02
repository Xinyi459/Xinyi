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
double* nextBoxS1(double *boxS);

#endif /* TreeforS_h */
