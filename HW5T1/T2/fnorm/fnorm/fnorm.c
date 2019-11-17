//
//  fnorm.c
//  fnorm
//
//  Created by xinyi on 10/14/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fnorm.h"
double fnorm(double *A, size_t n_rows, size_t n_cols){
    int i;
    double sum,result;
    sum=0;
    for (i=0;i<=n_rows*n_cols+n_cols;i++){
        sum=sum+pow(A[i],2);
        }
    result=pow(sum,0.5);
    printf("%f\n",result);
    return result;
}
