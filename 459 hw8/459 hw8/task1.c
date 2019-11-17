//
//  task1.c
//  459 hw8
//
//  Created by xinyi on 11/12/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include "matmul.h"
#include <stdlib.h>
#include <time.h>


int main(){
    double *A;
    double *B;
    double *C;
    const size_t n=1000;
    A=(double*)malloc((int)n*(int)n*sizeof(double));
    B=(double*)malloc((int)n*(int)n*sizeof(double));
    int seed=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[i*n+j]=seed;
            B[i*n+j]=seed;
            seed+=1;
        }
    }
   
    
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    C=mmul1(A, B, n);
    end = clock();
    cpu_time_used = ((double) (end - start));
    printf("mmul1 used time:%.0f\n",cpu_time_used);
   
    start = clock();
    C=mmul2(A, B, n);
    end = clock();
    cpu_time_used = ((double) (end - start));
    printf("mmul2 used time:%.0f\n",cpu_time_used);
    
    int seed1=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            B[j*n+i]=seed1;
            seed1+=1;
        }
    }
  
    start = clock();
    C=mmul3(A, B, n);
    end = clock();
    cpu_time_used = ((double) (end - start));
    printf("mmul3 used time:%.0f\n",cpu_time_used);
    
    int seed2=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[j*n+i]=seed2;
            B[i*n+j]=seed2;
            seed2+=1;
        }
    }

    
    start = clock();
    C=mmul4(A, B, n);
    end = clock();
    cpu_time_used = ((double) (end - start));
    printf("mmul4 used time:%.0f\n",cpu_time_used);
    
    printf("A,B,C are %ld * %ld matrix\n",n,n);
  
    free(A);
    free(B);
    free(C);
    
    
    
    
    
    return 0;
}
