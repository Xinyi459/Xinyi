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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
  int *colli;
  int numT = getT("/Users/user/Documents/Xcode/Practice/459FinalProject/"
                  "459FinalProject/mesh.csv");
  int numS = getS("/Users/user/Documents/Xcode/Practice/459FinalProject/"
                  "459FinalProject/sphere.csv");
  colli = collision("/Users/user/Documents/Xcode/Practice/459FinalProject/"
                    "459FinalProject/mesh.csv",
                    "/Users/user/Documents/Xcode/Practice/459FinalProject/"
                    "459FinalProject/sphere.csv");
  for (int i = 0; i < numS; i++) {
      for(int j=0;j<numT;j++){
          if(colli[i*numT+j]==0){
              printf("the %dth sphere contact with the %dth triangle\n",i+1,j+1);
          }
      }
  }
    
  return 0;
}
