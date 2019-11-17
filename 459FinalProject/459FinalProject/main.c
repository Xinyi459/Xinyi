//
//  main.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getData.h"
#include "getNum.h"
#include "getCond.h"
#include "collision.h"

int main(int argc, const char * argv[]) {
    int*colli;
    int numT=getT("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/mesh.csv");
    int numS=getS("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/sphere.csv");
    colli=collision("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/mesh.csv","/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/sphere.csv");
    for(int i=0;i<numT*numS;i++){
        printf("%d\n",colli[i]);
    }
    return 0;
}

  
