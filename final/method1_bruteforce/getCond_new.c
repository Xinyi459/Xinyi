//
//  getCond_new.c
//  459
//
//  Created by xinyi on 12/9/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "getCond_new.h"
#include "getData.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//************************************************************************
//
//! \brief Get the plane equation of triangular mesh(ax + by + cz + d = 0)
//
//************************************************************************
double *GetplaneT(double triangle_data[9]) {
  double *plane;
  double a, b, c, d;
  plane = (double *)malloc(4 * sizeof(double));
  a = (triangle_data[4] - triangle_data[1]) *
          (triangle_data[8] - triangle_data[2]) -
      (triangle_data[7] - triangle_data[1]) *
          (triangle_data[5] - triangle_data[2]);
  b = (triangle_data[5] - triangle_data[2]) *
          (triangle_data[6] - triangle_data[0]) -
      (triangle_data[8] - triangle_data[2]) *
          (triangle_data[3] - triangle_data[0 * 9]);
  c = (triangle_data[3] - triangle_data[0]) *
          (triangle_data[7] - triangle_data[1]) -
      (triangle_data[6] - triangle_data[0]) *
          (triangle_data[4] - triangle_data[1]);
  d = -a * triangle_data[0] - b * triangle_data[1] - c * triangle_data[2];
  plane[0] = a;
  plane[1] = b;
  plane[2] = c;
  plane[3] = d;
  return plane;
}

//************************************************************************
//
//! \brief Computing project point of sphere center on each plane
//
//************************************************************************
double *project(double triangle_data[9], double sphere_data[4]) {
  double *plane = GetplaneT(triangle_data);
  double *centerP;
  double center[3];
  for (int i = 0; i < 3; i++) {
    center[i] = sphere_data[i];
  }
  centerP = (double *)malloc(3 * sizeof(double));
  centerP[0] = center[0] - plane[0] *
                               (plane[0] * center[0] + plane[1] * center[1] +
                                plane[2] * center[2] + plane[3]) /
                               (plane[0] * plane[0] + plane[1] * plane[1] +
                                plane[2] * plane[2]);
  centerP[1] = center[1] - plane[1] *
                               (plane[0] * center[0] + plane[1] * center[1] +
                                plane[2] * center[2] + plane[3]) /
                               (plane[0] * plane[0] + plane[1] * plane[1] +
                                plane[2] * plane[2]);
  centerP[2] = center[2] - plane[2] *
                               (plane[0] * center[0] + plane[1] * center[1] +
                                plane[2] * center[2] + plane[3]) /
                               (plane[0] * plane[0] + plane[1] * plane[1] +
                                plane[2] * plane[2]);
  return centerP;
}

double *CrossMatrix(double *vect) {
  double *C;
  C = (double *)malloc(9 * sizeof(double));
  C[0] = 0;
  C[1] = -vect[2];
  C[2] = vect[1];
  C[3] = vect[2];
  C[4] = 0;
  C[5] = -vect[0];
  C[6] = -vect[1];
  C[7] = vect[0];
  C[8] = 0;
  return C;
}






//************************************************************************************
//
//! \brief Determine if a team of balls and grids collide，return 0 means no collision
//
//************************************************************************************
int colli(double triangle_data[9], double sphere_data[4]) {
  double center[3];
  for (int i = 0; i < 3; i++) {
    center[i] = sphere_data[i];
  }
  double *centerP = project(triangle_data, sphere_data);
  // get cross product
  double *C;        // the cross matrix PA
  double *anotherC; // CA
  C = (double *)malloc(9 * sizeof(double));
  anotherC = (double *)malloc(9 * sizeof(double));

  double *vect;
  vect = (double *)malloc(3 * sizeof(double));
  double *refvect;
  refvect = (double *)malloc(3 * sizeof(double));
  double *anotherLine;
  anotherLine = (double *)malloc(3 * sizeof(double));
  // store cos from dot product
  double *Dot;
  Dot = (double *)malloc(3 * sizeof(double));
  // x
  vect[0] = centerP[0] - triangle_data[0]; // PA
  refvect[0] =
      triangle_data[0] - triangle_data[3]; // the line used for cross product AB
  anotherLine[0] = triangle_data[6] - triangle_data[0]; // CA
  // y
  vect[1] = centerP[1] - triangle_data[1];
  refvect[1] = triangle_data[1] - triangle_data[4];
  anotherLine[1] = triangle_data[7] - triangle_data[1];
  // z
  vect[2] = centerP[2] - triangle_data[2];
  refvect[2] = triangle_data[2] - triangle_data[5];
  anotherLine[2] = triangle_data[8] - triangle_data[2];
  // get crossporduct
  // PA x AB CA x AB
  C = CrossMatrix(vect);
  anotherC = CrossMatrix(anotherLine);
  double c[3];
  double anotherc[3];
  for (int i = 0; i < 3; i++) {
    c[i] = C[i * 3 + 0] * refvect[0] + C[i * 3 + 1] * refvect[1] +
           C[i * 3 + 2] * refvect[2];
    anotherc[i] = anotherC[i * 3 + 0] * refvect[0] +
                  anotherC[i * 3 + 1] * refvect[1] +
                  anotherC[i * 3 + 2] * refvect[2];
  }
  for (int i = 0; i < 3; i++) {
    Dot[0] += c[i] * anotherc[i];
  }

  // x
  vect[0] = centerP[0] - triangle_data[3]; // PB
  refvect[0] =
      triangle_data[3] - triangle_data[6]; // the line used for cross product BC
  anotherLine[0] = triangle_data[0] - triangle_data[3]; // AB
  // y
  vect[1] = centerP[1] - triangle_data[4];
  refvect[1] = triangle_data[4] - triangle_data[7];
  anotherLine[1] = triangle_data[1] - triangle_data[4];
  // z
  vect[2] = centerP[2] - triangle_data[5];
  refvect[2] = triangle_data[5] - triangle_data[8];
  anotherLine[2] = triangle_data[2] - triangle_data[5];
  // get crossporduct

  C = CrossMatrix(vect);
  anotherC = CrossMatrix(anotherLine);
  for (int i = 0; i < 3; i++) {
    c[i] = C[i * 3 + 0] * refvect[0] + C[i * 3 + 1] * refvect[1] +
           C[i * 3 + 2] * refvect[2];
    anotherc[i] = anotherC[i * 3 + 0] * refvect[0] +
                  anotherC[i * 3 + 1] * refvect[1] +
                  anotherC[i * 3 + 2] * refvect[2];
  }
  for (int i = 0; i < 3; i++) {
    Dot[1] += c[i] * anotherc[i];
  }

  // x
  vect[0] = centerP[0] - triangle_data[6]; // PC
  refvect[0] =
      triangle_data[6] - triangle_data[0]; // the line used for cross product CA
  anotherLine[0] = triangle_data[3] - triangle_data[6]; // BC
  // y
  vect[1] = centerP[1] - triangle_data[7];
  refvect[1] = triangle_data[7] - triangle_data[1];
  anotherLine[1] = triangle_data[4] - triangle_data[7];
  // z
  vect[2] = centerP[2] - triangle_data[8];
  refvect[2] = triangle_data[8] - triangle_data[2];
  anotherLine[2] = triangle_data[5] - triangle_data[8];
  // get crossporduct

  C = CrossMatrix(vect);
  anotherC = CrossMatrix(anotherLine);
  for (int i = 0; i < 3; i++) {
    c[i] = C[i * 3 + 0] * refvect[0] + C[i * 3 + 1] * refvect[1] +
           C[i * 3 + 2] * refvect[2];
    anotherc[i] = anotherC[i * 3 + 0] * refvect[0] +
                  anotherC[i * 3 + 1] * refvect[1] +
                  anotherC[i * 3 + 2] * refvect[2];
  }
  for (int i = 0; i < 3; i++) {
    Dot[2] += c[i] * anotherc[i];
  }

  // in or out
  int flag = 1; // in the triangle
  for (int i = 0; i < 3; i++) {
    if (Dot[i] < 0) {
      flag = 0;
    }
  }
  // collision or not; 1 means collision
  double r = sphere_data[3];
  int colli = 0;
  double dist = 0;
    double test1=0;
    double test2=0;
    double test3=0;
  double line1[3], line2[3];
  if (flag == 1) {
    for (int i = 0; i < 3; i++) {
      dist += (center[i] - centerP[i]) * (center[i] - centerP[i]);
    }
    dist = fabs(sqrt(dist));
    if (dist <= r) {
      colli = 1;
      dist = 0;
    }
    dist = 0;
  } else {

    for (int i = 0; i < 3; i++) {
      line1[i] = center[i] - triangle_data[i];            // PA
      line2[i] = triangle_data[3 + i] - triangle_data[i]; // BA
    }
      
    for (int i = 0; i < 3; i++) {
      dist += line1[i] * line2[i];
    }
      test1=dist / (sqrt(line2[0] * line2[0] + line2[1] * line2[1] +
                        line2[2] * line2[2])*sqrt(line1[0] * line1[0] + line1[1] * line1[1] +
                                                  line1[2] * line1[2]));
      
    dist = fabs(dist) / sqrt(line2[0] * line2[0] + line2[1] * line2[1] +
                             line2[2] * line2[2]);
     
    dist = sqrt(pow(line1[0], 2) + pow(line1[1], 2) + pow(line1[2], 2) -
                pow(dist, 2));
    if (dist <= r) {
      colli = 1;
        if(fabs(test1)==1){
            if(pow(line1[0], 2) + pow(line1[1], 2) + pow(line1[2], 2)&&(pow((center[0]-triangle_data[3+0]),2)+pow((center[1]-triangle_data[3+1]),2)+pow((center[2]-triangle_data[3+2]),2))>r*r){
                colli=0;
            }
        }
    }
    dist = 0;

    for (int i = 0; i < 3; i++) {
      line1[i] = center[i] - triangle_data[3 + i];            // PB
      line2[i] = triangle_data[6 + i] - triangle_data[3 + i]; // CB
    }
    for (int i = 0; i < 3; i++) {
      dist += line1[i] * line2[i];
    }
      test2=dist / (sqrt(line2[0] * line2[0] + line2[1] * line2[1] +
                        line2[2] * line2[2])*sqrt(line1[0] * line1[0] + line1[1] * line1[1] +
                                                  line1[2] * line1[2]));
    dist = fabs(dist) / sqrt(line2[0] * line2[0] + line2[1] * line2[1] +
                             line2[2] * line2[2]);
      
    dist = sqrt(pow(line1[0], 2) + pow(line1[1], 2) + pow(line1[2], 2) -
                pow(dist, 2));

      if (dist <= r) {
          colli = 1;
          if(fabs(test2)==1){
              if(pow(line1[0], 2) + pow(line1[1], 2) + pow(line1[2], 2)&&(pow((center[0]-triangle_data[6+0]),2)+pow((center[1]-triangle_data[6+1]),2)+pow((center[2]-triangle_data[6+2]),2))>r*r){
                  colli=0;
              }
          }
      }
    dist = 0;

    for (int i = 0; i < 3; i++) {
      line1[i] = center[i] - triangle_data[6 + i];        // PC
      line2[i] = triangle_data[i] - triangle_data[6 + i]; // AC
    }

    for (int i = 0; i < 3; i++) {
      dist += line1[i] * line2[i];
    }
      test3=dist / (sqrt(line2[0] * line2[0] + line2[1] * line2[1] +
                       line2[2] * line2[2])*sqrt(line1[0] * line1[0] + line1[1] * line1[1] +
                                                 line1[2] * line1[2]));
    dist = fabs(dist) / sqrt(line2[0] * line2[0] + line2[1] * line2[1] +
                             line2[2] * line2[2]);
      
    dist = sqrt(pow(line1[0], 2) + pow(line1[1], 2) + pow(line1[2], 2) -
                pow(dist, 2));
      if (dist <= r) {
          colli = 1;
          if(fabs(test3)==1){
              if(pow(line1[0], 2) + pow(line1[1], 2) + pow(line1[2], 2)&&(pow((center[0]-triangle_data[0]),2)+pow((center[1]-triangle_data[1]),2)+pow((center[2]-triangle_data[2]),2))>r*r){
                  colli=0;
              }
          }
      }
    dist = 0;
  }
    free(C);
    free(anotherC);
    free(vect);
    free(refvect);
    free(anotherLine);
    free(Dot);
    
  return colli;
}
