//
//  main.c
//  HW4T1
//
//  Created by xinyi on 10/7/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
int main(int argc, const char * argv[]) {
    printf("size of struct A : %ld\n",sizeof(struct A));
    printf("size of struct B : %ld\n",sizeof(struct B));
    struct A*A1=(struct A*)malloc(1*sizeof(struct A));
    A1->i=10;
    A1->c='c';
    A1->d=123;
    printf("i in struct A = %d\n",A1->i);
    printf("c in struct A = %c\n",A1->c);
    printf("d in struct A = %f\n",A1->d);
    free(A1);
}
