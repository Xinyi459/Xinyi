//
//  getCond_new.h
//  459
//
//  Created by xinyi on 12/9/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#ifndef getCond_new_h
#define getCond_new_h

#include <stdio.h>

double *GetplaneT(ouble triangle_data[9]);

double *project(double triangle_data[9], double sphere_data[4]);

double *CrossMatrix(double *vect);

///1 means in, 0 means out
///1 means colli, 0 means no
int colli(double triangle_data[9], double sphere_data[4]);
#endif /* getCond_new_h */
