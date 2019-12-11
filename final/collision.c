//
//  collision.c
//  459FinalProject
//
//  Created by xinyi on 11/16/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "collision.h"
#include "getCond.h"
#include "getData.h"
#include "getCond_new.h"
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
    double *A=ReadCSV(filenameT);
    int numT = A[0];
    double *B=ReadCSV(filenameS);
    int numS = B[4];
    double P[9];
    double Pc[3];
    double vectc[9];
    double refvect[9];
    int *collision;
    collision = (int *)malloc(numT * numS * sizeof(int));
    clock_t start = clock();
    for (int i = 0; i < numT * numS; i++) {
        collision[i] = 1; // 1 means no collision
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
                        P[a * 3 + b] = Apex[j * 9 + a * 3 + b];
                    }
                }
                for (int vc = 0; vc < 3; vc++) { // which apex
                    for (int i = 0; i < 3; i++) {  // x,y,z?
                        vectc[vc * 3 + i] = Pc[i] - P[vc * 3 + i];
                    }
                }
                for (int v = 0; v < 2; v++) {
                    for (int i = 0; i < 3; i++) {
                        refvect[v * 3 + i] = P[(v + 1) * 3 + i] - P[v * 3 + i];
                    }
                }
                refvect[6] = P[0] - P[6];
                refvect[7] = P[1] - P[7];
                refvect[8] = P[2] - P[8];
                // computing distance d
                // double*refmatrix=CrossMatrix(refvect);
                // AB X AC
                // a center with a triangle
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        double v1[3] = {vectc[i * 3 + 0], vectc[i * 3 + 1],
                            vectc[i * 3 + 2]};
                        double v2[3] = {refvect[j * 3 + 0], refvect[j * 3 + 1],
                            refvect[j * 3 + 2]};
                        // v2 X v1
                        double *v2matrix = CrossMatrix(v2);
                        double *crossproduct;
                        crossproduct = (double *)malloc(3 * sizeof(double));
                        for (int i = 0; i < 3; i++) {
                            crossproduct[i] = v2matrix[i * 3 + 0] * v1[0] +
                            v2matrix[i * 3 + 1] * v1[1] +
                            v2matrix[i * 3 + 2] * v1[2];
                        }
                        double ab = 0;
                        for (int i = 0; i < 3; i++) {
                            ab += v2[i] * v2[i];
                        }
                        ab = sqrt(ab);
                        double d[3];
                        for (int i = 0; i < 3; i++) {
                            d[i] = crossproduct[i] / ab;
                        }
                        double distance = 0;
                        for (int i = 0; i < 3; i++) {
                            distance += d[i] * d[i];
                        }
                        distance = sqrt(distance);
                        if (distance > r) {
                            continue;
                        } else {
                            collision[c] = 0;
                            break;
                        }
                    }
                }
                c += 1;
            }
            ////////////////////////////////////////////////////////////////////////////
            else {
                double *centerP = CenterToP(filenameT, filenameS);
                // get the direction from Pc to centerP
                double dis[3];
                for (int k = 0; k < 3; k++) {
                    dis[k] += Pc[k] - centerP[i * 6 + j * 3 + k];
                }
                double distance = 0;
                for (int d = 0; d < 3; d++) {
                    distance += dis[d] * dis[d];
                }
                distance = sqrt(distance);
                if (distance > r) {
                    c += 1;
                    continue;
                } else {
                    collision[c] = 0;
                    c += 1;
                    break;
                }
            }
        }
    }
    clock_t end = clock();
    double time = (double)(end- start) ;
    printf("the first method used time: %f\n",time);
    return collision;
}
