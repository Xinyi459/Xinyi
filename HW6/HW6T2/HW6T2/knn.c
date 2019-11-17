//
//  knn.c
//  HW6T2
//
//  Created by xinyi on 10/19/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "knn.h"
double compute_distances(double *train_instances,double *test_instance,int n_train, int n_features){
    int i,j,k,n,m;
    double result;
    for (k=0;k<n_train;k++){
        result=0;
        for (i=k;i<k+1;i++){
            for (j=0;j<n_features;j++){
                result =result+fabs(test_instance[j]-train_instances[i*n_features+j]);
            }
        }
        printf("%f ",result);
    }
    printf("\n");
    return 0;
}
                    

