//
//  main.c
//  HW4T2
//
//  Created by xinyi on 10/7/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mvmul.h"


int main(int argc, const char * argv[]) {
    size_t n;
    double *A;
    double *b;
    double *c;
    const char *str = argv[1];
    n=atoi(str);
    //n=3;
    A=(double *)malloc(n*n*sizeof(double));
    b=(double *)malloc(n*sizeof(double));
    int i,j,k;
    for (i=0;i<n;i++){
        b[i]=1.0;
        for (j=0;j<n;j++){
            A[i * n + j]=i;
        }
    }
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    c=mvmul(A,b,n);
    end = clock();
    cpu_time_used = ((double) (end - start));
    for (k=0;k<n;k++)
        printf("%.0f\n",c[k]);
    free(A);
    free(b);
    free(c);
    printf("%.0f\n",cpu_time_used);
}
