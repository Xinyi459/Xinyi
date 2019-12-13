//
//  main.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "collision.h"
#include "getCond.h"
#include "getCond_new.h"
#include "getData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
  const char *filenameS =
      "D:/Courses/ME459/finalProject/src/Xinyi/Xinyi/final/sphere.csv";
  // const char *filenameT
  // ="/Users/user/Documents/Xcode/Practice/459/459/bunny_mesh1.csv";
  const char *filenameT =
      "D:/Courses/ME459/finalProject/src/Xinyi/Xinyi/final/mesh.csv";

  ///////////////first method////////////
  int *colli;
  colli = collision(filenameT, filenameS);

  ////////////////second method//////////////

  ///////////////output//////////////////////

  double *A = ReadCSV(filenameT);
  int numT = A[0];
  double *B = ReadCSV(filenameS);
  int numS = B[4];
  FILE *fp = NULL;
  fp = fopen("/Users/user/Desktop/output/output.csv", "w");
  if (NULL == fp) {
    return -1;
  }
  fprintf(fp, "%s,%s\n", "s", "t");
  for (int i = 0; i < numS; i++) {
    for (int j = 0; j < numT; j++) {
      if (colli[i * numT + j] == 1) {
        fprintf(fp, "%d,%d\n", i, j);
      }
    }
  }
  fclose(fp);
  fp = NULL;

  /*
   double T[9]={0,-2,0,
       2,2,0,
       -2,2,0};
   double S[4]={0,0,3.1,3};
   int collis=colli(T,S);
   printf("%d\n",collis);
   */
  return 0;
}
