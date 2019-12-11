//
//  main.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "collision.h"
#include "getCond.h"
#include "getData.h"
#include "getCond_new.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>




int main(int argc, const char *argv[]) {
    ///////////////first method////////////
    int *colli;
    colli = collision("/Users/user/Documents/Xcode/Practice/459/459/mesh.csv",
                      "/Users/user/Documents/Xcode/Practice/459/459/sphere.csv");
    
    ////////////////second method//////////////

    

    
    
    
    ///////////////output//////////////////////
    double *A=ReadCSV("/Users/user/Documents/Xcode/Practice/459/459/mesh.csv");
    int numT = A[0] ;
    double *B=ReadCSV("/Users/user/Documents/Xcode/Practice/459/459/sphere.csv");
    int numS = B[4] ;
    FILE *fp = NULL;
    fp = fopen("/Users/user/Desktop/output/output.csv", "a");
    if(NULL == fp)
    {
        return -1;
    }
    fprintf(fp,"%s,%s\n","s","t");
    for (int i = 0; i < numS; i++) {
        for(int j=0;j<numT;j++){
            if(colli[i*numT+j]==0){
                fprintf(fp,"%d,%d\n",i,j);
            }
        }
    }
    fclose(fp);
    fp = NULL;
     
    
    return 0;
}
