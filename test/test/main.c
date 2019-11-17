//
//  main.c
//  test
//
//  Created by xinyi on 10/9/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>







int main(){
    double *vals;
    size_t n_vals=10;
    //printf("%ld\n",vals[1]);
    vals=(double *)malloc(sizeof(double)*n_vals);
    int prod=1;
    size_t i;
    for (i=0;i<=n_vals;i++){
        vals[i]=i+1;
        printf("%d\n",vals[i]);
        prod *=i+1;
        printf("%d\n",prod);
    }
    
    return 0;
    
}


