//
//  matmul.c
//  459 hw8
//
//  Created by xinyi on 11/11/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include "matmul.h"
#include <stdlib.h>

double* mmul1(const double* A, const double* B, const size_t n){
    double *C;
    C=(double*)malloc((int)n*(int)n*sizeof(double));
    for(int i=0; i<(int)n;i++){
        for(int j=0;j<(int)n;j++){
            for(int k=0;k<(int)n;k++){
                C[i*(int)n+j]=A[i*(int)n+k]*B[(int)n*k+j];
            }
        }
    }
    return C;
}

double* mmul2(const double* A, const double* B, const size_t n){
    double *C;
    C=(double*)malloc((int)n*(int)n*sizeof(double));
    for(int j=0; j<(int)n;j++){//col
        for(int i=0;i<(int)n;i++){//row
            for(int k=0;k<(int)n;k++){
                C[i*(int)n+j]=A[i*(int)n+k]*B[(int)n*k+j];
            }
        }
    }
    return C;
}

double* mmul3(const double* A, const double* B, const size_t n){
    double *C;
    C=(double*)malloc((int)n*(int)n*sizeof(double));
    for(int i=0; i<(int)n;i++){
        for(int j=0;j<(int)n;j++){
            for(int k=0;k<(int)n;k++){
                C[i*(int)n+j]=A[i*(int)n+k]*B[j*(int)n+k];
            }
        }
    }
    return C;
}

double* mmul4(const double* A, const double* B, const size_t n){
    double *C;
    C=(double*)malloc((int)n*(int)n*sizeof(double));
    for(int i=0; i<(int)n;i++){
        for(int j=0;j<(int)n;j++){
            for(int k=0;k<(int)n;k++){
                C[i*(int)n+j]=A[(int)n*k+i]*B[(int)n*k+j];
            }
        }
    }
    return C;
}
