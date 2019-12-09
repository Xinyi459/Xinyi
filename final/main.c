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
#include "getNum.h"
#include "TreeforS.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>




int main(int argc, const char *argv[]) {
 ///////////////first method//////////////
  int *colli;
  int numT = getT("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/mesh.csv");
  int numS = getS("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/sphere.csv");
  colli = collision("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/mesh.csv",
                    "/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/sphere.csv");
////////////////second method//////////////
    

///////////////output//////////////////////
    FILE *fp = NULL;
    fp = fopen("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/output.csv", "a");
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
