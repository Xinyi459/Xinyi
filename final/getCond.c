//
//  getCond.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "getCond.h"
#include "getCond_new.h"
#include "getData.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double *
Getplane(const char *filename) { // the number of apexs is len*3/4，number of
  // triangles is lenT/4
  double *Apex = getApex(filename);
  double *A = ReadCSV(filename);
  int lenT = A[0] * 4;
  double *plane, *a, *b, *c, *d;
  plane = (double *)malloc(lenT * 4 / 3 * sizeof(double));
  a = (double *)malloc(lenT / 4 * sizeof(double));
  b = (double *)malloc(lenT / 4 * sizeof(double));
  c = (double *)malloc(lenT / 4 * sizeof(double));
  d = (double *)malloc(lenT / 4 * sizeof(double));
  // loop based on the number of triangles
  for (int i = 0; i < lenT / 4; i++) {
    a[i] = (Apex[i * 9 + 4] - Apex[i * 9 + 1]) *
               (Apex[i * 9 + 8] - Apex[i * 9 + 2]) -
           (Apex[i * 9 + 7] - Apex[i * 9 + 1]) *
               (Apex[i * 9 + 5] - Apex[i * 9 + 2]);
    b[i] =
        (Apex[i * 9 + 5] - Apex[i * 9 + 2]) *
            (Apex[i * 9 + 6] - Apex[i * 9 + 0]) -
        (Apex[i * 9 + 8] - Apex[i * 9 + 2]) * (Apex[i * 9 + 3] - Apex[i * 9]);
    c[i] = (Apex[i * 9 + 3] - Apex[i * 9 + 0]) *
               (Apex[i * 9 + 7] - Apex[i * 9 + 1]) -
           (Apex[i * 9 + 6] - Apex[i * 9 + 0]) *
               (Apex[i * 9 + 4] - Apex[i * 9 + 1]);
    d[i] = -a[i] * Apex[i * 9 + 0] - b[i] * Apex[i * 9 + 1] -
           c[i] * Apex[i * 9 + 2];
  }
  int step = 0;
  for (int i = 0; i < lenT / 4; i++) {
    plane[i * 4] = a[step];
    plane[i * 4 + 1] = b[step];
    plane[i * 4 + 2] = c[step];
    plane[i * 4 + 3] = d[step];
    step += 1;
  }

  return plane;
}

double *CenterToP(const char *filenameT, const char *filenameS) {
  double *center = getCenter(filenameS);
  double *plane = Getplane(filenameT);
  double *A = ReadCSV(filenameT);
  int lenT = A[0] * 4;
  double *B = ReadCSV(filenameS);
  int lens = B[4] * 3;
  double *centerP;
  centerP = (double *)malloc(lens * lenT / 4 * sizeof(double));
  int step = 0;
  for (int i = 0; i < lens / 3; i++) {
    for (int j = 0; j < lenT / 4; j++) {
      centerP[step] =
          center[i * 3] -
          plane[j * 4] *
              (plane[j * 4] * center[i * 3] +
               plane[j * 4 + 1] * center[i * 3 + 1] +
               plane[j * 4 + 2] * center[i * 3 + 2] + plane[j * 4 + 3]) /
              (plane[j * 4] * plane[j * 4] +
               plane[j * 4 + 1] * plane[j * 4 + 1] +
               plane[j * 4 + 2] * plane[j * 4 + 2]);
      centerP[step + 1] =
          center[i * 3 + 1] -
          plane[j * 4 + 1] *
              (plane[j * 4] * center[i * 3] +
               plane[j * 4 + 1] * center[i * 3 + 1] +
               plane[j * 4 + 2] * center[i * 3 + 2] + plane[j * 4 + 3]) /
              (plane[j * 4] * plane[j * 4] +
               plane[j * 4 + 1] * plane[j * 4 + 1] +
               plane[j * 4 + 2] * plane[j * 4 + 2]);
      centerP[step + 2] =
          center[i * 3 + 2] -
          plane[j * 4 + 2] *
              (plane[j * 4] * center[i * 3] +
               plane[j * 4 + 1] * center[i * 3 + 1] +
               plane[j * 4 + 2] * center[i * 3 + 2] + plane[j * 4 + 3]) /
              (plane[j * 4] * plane[j * 4] +
               plane[j * 4 + 1] * plane[j * 4 + 1] +
               plane[j * 4 + 2] * plane[j * 4 + 2]);
      step += 3;
    }
  }

  return centerP;
}

int *inORout(const char *filenameT, const char *filenameS) {
  double *Apex = getApex(filenameT);
  double *Project = CenterToP(filenameT, filenameS);
  double *A = ReadCSV(filenameT);
  int numT = A[0];
  double *B = ReadCSV(filenameS);
  int numS = B[4];
  // get cross product
  double *C; // the cross product
  double *anotherC;
  C = (double *)malloc(3 * sizeof(double));
  anotherC = (double *)malloc(3 * sizeof(double));

  // compute C
  double *cross; // the cross matrix
  double *anothercross;
  double *vect;
  vect = (double *)malloc(3 * sizeof(double));
  double *refvect;
  refvect = (double *)malloc(3 * sizeof(double));
  double *anotherLine;
  anotherLine = (double *)malloc(3 * sizeof(double));
  // store cos from dot product
  double *Dot;
  Dot = (double *)malloc(3 * numT * numS * sizeof(double));
  int d = 0;
  for (int i = 0; i < numS; i++) {
    for (int j = 0; j < numT; j++) {
      int k = 0;
      for (int v = 0; v < 3; v++) { // get vector from apex to project point
        vect[v] = Project[i * 3 + v] - Apex[j * 9 + k * 3 + v];
        refvect[v] = Apex[j * 9 + (k + 1) * 3 + v] -
                     Apex[j * 9 + k * 3 + v]; // the line used for cross product
        anotherLine[v] =
            Apex[j * 9 + (k + 2) * 3 + v] - Apex[j * 9 + k * 3 + v];
      }
      cross = CrossMatrix(vect);
      anothercross = CrossMatrix(anotherLine);
      for (int i = 0; i < 3; i++) {
        C[i] = cross[i * 3 + 0] * refvect[0] + cross[i * 3 + 1] * refvect[1] +
               cross[i * 3 + 2] * refvect[2];
        anotherC[i] = anothercross[i * 3 + 0] * refvect[0] +
                      anothercross[i * 3 + 1] * refvect[1] +
                      anothercross[i * 3 + 2] * refvect[2];
      }
      // compte their dot product to determine if their direction is the same
      double dot = 0;
      double a = 0;
      double b = 0;
      for (int i = 0; i < 3; i++) {
        a += C[i] * C[i];
        b += anotherC[i] * anotherC[i];
        dot += C[i] * anotherC[i];
      }
      Dot[d] = dot / (sqrt(a) * sqrt(b));
      d += 1;

      k = 1;
      for (int v = 0; v < 3; v++) { // get vector from apex to project point
        vect[v] = Project[i * 3 + v] - Apex[j * 9 + k * 3 + v];
      }
      refvect[0] = Apex[j * 9 + (k + 1) * 3 + 0] - Apex[j * 9 + k * 3 + 0];
      refvect[1] = Apex[j * 9 + (k + 1) * 3 + 1] - Apex[j * 9 + k * 3 + 1];
      refvect[2] = Apex[j * 9 + (k + 1) * 3 + 2] - Apex[j * 9 + k * 3 + 2];
      anotherLine[0] = Apex[j * 9 + 0 * 3 + 0] - Apex[j * 9 + k * 3 + 0];
      anotherLine[1] = Apex[j * 9 + 0 * 3 + 1] - Apex[j * 9 + k * 3 + 1];
      anotherLine[2] = Apex[j * 9 + 0 * 3 + 2] - Apex[j * 9 + k * 3 + 2];

      cross = CrossMatrix(vect);
      anothercross = CrossMatrix(anotherLine);
      for (int i = 0; i < 3; i++) {
        C[i] = cross[i * 3 + 0] * refvect[0] + cross[i * 3 + 1] * refvect[1] +
               cross[i * 3 + 2] * refvect[2];
        anotherC[i] = anothercross[i * 3 + 0] * refvect[0] +
                      anothercross[i * 3 + 1] * refvect[1] +
                      anothercross[i * 3 + 2] * refvect[2];
      }
      // compte their dot product to determine if their direction is the same
      dot = 0;
      a = 0;
      b = 0;
      for (int i = 0; i < 3; i++) {
        a += C[i] * C[i];
        b += anotherC[i] * anotherC[i];
        dot += C[i] * anotherC[i];
      }
      Dot[d] = dot / (sqrt(a) * sqrt(b));
      d += 1;

      k = 2;
      for (int v = 0; v < 3; v++) { // get vector from apex to project point
        vect[v] = Project[i * 3 + v] - Apex[j * 9 + k * 3 + v];
      }
      refvect[0] = Apex[j * 9 + 0 * 3 + 0] - Apex[j * 9 + k * 3 + 0];
      refvect[1] = Apex[j * 9 + 0 * 3 + 1] - Apex[j * 9 + k * 3 + 1];
      refvect[2] = Apex[j * 9 + 0 * 3 + 2] - Apex[j * 9 + k * 3 + 2];
      anotherLine[0] = Apex[j * 9 + 1 * 3 + 0] - Apex[j * 9 + k * 3 + 0];
      anotherLine[1] = Apex[j * 9 + 1 * 3 + 1] - Apex[j * 9 + k * 3 + 1];
      anotherLine[2] = Apex[j * 9 + 1 * 3 + 2] - Apex[j * 9 + k * 3 + 2];

      cross = CrossMatrix(vect);
      anothercross = CrossMatrix(anotherLine);
      for (int i = 0; i < 3; i++) {
        C[i] = cross[i * 3 + 0] * refvect[0] + cross[i * 3 + 1] * refvect[1] +
               cross[i * 3 + 2] * refvect[2];
        anotherC[i] = anothercross[i * 3 + 0] * refvect[0] +
                      anothercross[i * 3 + 1] * refvect[1] +
                      anothercross[i * 3 + 2] * refvect[2];
      }
      // compte their dot product to determine if their direction is the same
      dot = 0;
      a = 0;
      b = 0;
      for (int i = 0; i < 3; i++) {
        a += C[i] * C[i];
        b += anotherC[i] * anotherC[i];
        dot += C[i] * anotherC[i];
      }
      Dot[d] = dot / (sqrt(a) * sqrt(b));
      d += 1;
    }
  }
  int *Inout;
  Inout = (int *)malloc(numT * numS * sizeof(int));
  int step = 0;
  for (int i = 0; i < numS; i++) {
    for (int j = 0; j < numT; j++) {
      for (int k = 0; k < 3; k++) {
        double dot = Dot[i * numT * 3 + j * 3 + k];
        Inout[step] = 1; // 1 means in
        if (dot < 0)
          Inout[step] = 0;
        ;
        break;
      }
      step += 1;
    }
  }
  return Inout;
}
