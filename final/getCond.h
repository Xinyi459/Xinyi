//
//  getCond.h
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#ifndef getCond_h
#define getCond_h

#include <stdio.h>
//get the plane of triangles, return a b c d which set up plane function
double *Getplane(const char *filename);
//get center's projection on triangle plane
double *CenterToP(const char *filenameT,const char *filenameS);
//get cross matrix
double *CrossMatrix(double*vect);
//huge function, get an array filled with 0 or 1, 0 mean the sphere's possible collision point is not in the triangle
//0 and 1 stored with sphere major
int* inORout(const char *filenameT,const char *filenameS);
#endif /* getCond_h */
