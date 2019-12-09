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

double *GetplaneT(int pair[2],const char *filenameT);

double*project(int pair[2],const char *filenameT,const char *filenameS);

double *CrossMatrix(double *vect);

///1 means in, 0 means out
int in_or_out(int pair[2],const char *filenameT,const char *filenameS);
#endif /* getCond_new_h */
