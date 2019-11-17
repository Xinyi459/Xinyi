// Author: Nic Olsen

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matmul.h"

// TODO: explain this
double* (*mmuls[])(const double*, const double*, const size_t) = {mmul1, mmul2,
    mmul3, mmul4};

int main(int argc, char* argv[]) {
    // Matrix dimension
    const size_t n = 2;
    
    // Allocate and fill square matrices with all elements 1.0
    double* A = (double*)malloc(n * n * sizeof(double));
    double* B = (double*)malloc(n * n * sizeof(double));
    
    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            A[row * n + col] = 1.0;
            B[row * n + col] = 1.0;
        }
    }
    
    // Compute reference solution
    double* C_ref = (double*)calloc(n * n, sizeof(double));
    for (size_t row = 0; row < n; row++) {
        for (size_t col = 0; col < n; col++) {
            for (size_t k = 0; k < n; k++) {
                C_ref[row * n + col] += A[row * n + k] * B[k * n + col]; //2222
            }
        }
    }
   
    
    for (size_t i = 0; i < 4; i++) {
        // NOTE: This is only ok because A and B have all entries the same so
        // that they are both the same stored in row major and in column major
        // orders. If they weren't all the same entry, they would need to be
        // rearranged according to the storage pattern expected by the function.
        // TODO: explain this
        double* C = (*mmuls[i])(A, B, n);
        
        double err = 0.0;
        for (size_t row = 0; row < n; row++) {
            for (size_t col = 0; col < n; col++) {
                double d = C_ref[row * n + col] - C[row * n + col]; //1
                err += d * d; //1
            }
        }
        //printf("%f\n", err);
        //err=sqrt(4);
        err = sqrt(err);
        //printf("mmul%lu error: %f\n", i + 1, err);
        free(C);
    }
    
    
    
    
    
    free(C_ref);
    return 0;
}
