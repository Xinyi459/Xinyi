//
//  collision.h
//  459FinalProject
//
//  Created by xinyi on 11/16/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#ifndef collision_h
#define collision_h

#include <stdio.h>
///in the array, 0 means no collision, 1 means collision, the array is filled with sphere major
///it stored the collision condition of each sphere with every triangle
int *collision(const char *filenameT,const char *filenameS);
#endif /* collision_h */
