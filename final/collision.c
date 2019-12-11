//
//  collision.c
//  459FinalProject
//
//  Created by xinyi on 11/16/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "collision.h"
#include "getCond.h"
#include "getCond_new.h"
#include "getData.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int *collision(const char *filenameT, const char *filenameS) {
  double *S = ReadCSV(filenameS);
  int r = S[3];
  double *Apex = getApex(filenameT);
  double *center = getCenter(filenameS);
    
  int *Inout = inORout(filenameT, filenameS);
   
  double *A = ReadCSV(filenameT);
  int numT = A[0];
  double *B = ReadCSV(filenameS);
  int numS = B[4];
  double P[9];
  double *Pc;
    Pc=(double*)malloc(3*sizeof(double));
  double vectc[9];
  double refvect[9];
  int *collision;
  collision = (int *)malloc(numT * numS * sizeof(int));
  clock_t start = clock();
  for (int i = 0; i < numT * numS; i++) {
    collision[i] = 0; // 0 means no collision
  }
  int c = 0;                       // for array collision
  for (int i = 0; i < numS; i++) { // the number of sphere
    Pc[0] = center[i * 3 + 0];
    Pc[1] = center[i * 3 + 1];
    Pc[2] = center[i * 3 + 2];
    //////////////////////////////////////////////////
    for (int j = 0; j < numT; j++) { // the number of triangle
      // find outside center
      if (Inout[i * numT + j] == 0) {
        for (int a = 0; a < 3; a++) {
          for (int b = 0; b < 3; b++) {
            P[a * 3 + b] = Apex[j * 9 + a * 3 + b]; // current mesh
          }
        }
        for (int vc = 0; vc < 3; vc++) {               // which apex
          for (int i = 0; i < 3; i++) {                // x,y,z?
            vectc[vc * 3 + i] = Pc[i] - P[vc * 3 + i]; // AP BP CP
          }
        }
        // AB BC CA
        refvect[0] = P[3] - P[0];
        refvect[1] = P[4] - P[1];
        refvect[2] = P[5] - P[2];
        refvect[3] = P[6] - P[3];
        refvect[4] = P[7] - P[4];
        refvect[5] = P[8] - P[5];
        refvect[6] = P[0] - P[6];
        refvect[7] = P[1] - P[7];
        refvect[8] = P[2] - P[8];
        // computing distance d between each line with center
        double dist = 0;
        double line1[3], line2[3];
        for (int i = 0; i < 3; i++) {
          line1[i] = Pc[i] - P[i]; // AP
          line2[i] = refvect[i];   // AB
        }

        for (int i = 0; i < 3; i++) {
          dist += pow(line1[i] * line2[i], 2);
        }
        dist =
            fabs(sqrt(dist) / sqrt(line2[0] * line2[0] + line2[1] * line2[1] +
                                   line2[2] * line2[2]));
          dist=fabs(sqrt(pow(line1[0],2)+pow(line1[1],2)+pow(line1[1],2)-pow(dist,2)));
        if (dist <= r) {
          collision[c] = 1;
        }
        dist = 0;

        for (int i = 0; i < 3; i++) {
          line1[i] = Pc[i] - P[i];   // BP
          line2[i] = refvect[3 + i]; // BC
        }

        for (int i = 0; i < 3; i++) {
          dist += pow(line1[i] * line2[i], 2);
        }
        dist =
            fabs(sqrt(dist) / sqrt(line2[0] * line2[0] + line2[1] * line2[1] +
                                   line2[2] * line2[2]));
          dist=fabs(sqrt(pow(line1[0],2)+pow(line1[1],2)+pow(line1[1],2)-pow(dist,2)));
        if (dist <= r) {
          collision[c] = 1;
        }
        dist = 0;

        for (int i = 0; i < 3; i++) {
          line1[i] = Pc[i] - P[i];   // CP
          line2[i] = refvect[6 + i]; // CA
        }

        for (int i = 0; i < 3; i++) {
          dist += pow(line1[i] * line2[i], 2);
        }
        dist =
            fabs(sqrt(dist) / sqrt(line2[0] * line2[0] + line2[1] * line2[1] +
                                   line2[2] * line2[2]));
          dist=fabs(sqrt(pow(line1[0],2)+pow(line1[1],2)+pow(line1[1],2)-pow(dist,2)));
        if (dist <= r) {
          collision[c] += 1;
        }
        dist = 0;
        c += 1;
      }
      ////////////////////////////////////////////////////////////////////////////
      else {
        double *centerP = CenterToP(filenameT, filenameS);
         
          
        // get the direction from Pc to centerP
        double dis[3];
        double distance;
          for (int k = 0; k < 3; k++) {
              dis[k] =0;
          }
        for (int k = 0; k < 3; k++) {
          dis[k] += Pc[k] - centerP[i * numT*3 + j * 3 + k];
        }
         
        distance=0;
        for (int d = 0; d < 3; d++) {
          distance += pow(dis[d], 2);
        }
        distance = fabs(sqrt(distance));
          
         if(distance<=r) {
          collision[c] += 1;
          c+= 1;
        }
          c+=1;
      }
    }
  }
  clock_t end = clock();
  double time = (double)(end - start);
  printf("the first method used time: %f\n", time);
  return collision;
}
