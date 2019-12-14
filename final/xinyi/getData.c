//
//  getData.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "getData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double *ReadCSV(const char *filename) {
  FILE *fp;
  fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "failed to open file for reading\n");
    exit(1);
  }
  char *line, *record;
  char buffer[1024];
  double value;
  int n = 0;
  while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL) {
    n += 1;
  }
  fclose(fp);
  // put values in csv file into array A
  int m = n*4;
  double *A;
  A = (double *)malloc(m * sizeof(double));
  fp = fopen(filename, "r");
  int i = 0;
  while ((line = fgets(buffer, sizeof(buffer), fp)) != NULL) {
    record = strtok(line, ",");
    while (record != NULL) {
      value = atof(record);
      A[i] = value;
      record = strtok(NULL, ",");
      i += 1;
    }
  }
  fclose(fp);
  return A;
}

double *getApex(const char *filename) {
  double *T;
  double *Apex;
  T = ReadCSV(filename);
  double num = T[0];
  Apex = (double *)malloc(num * 9 * sizeof(double));
  int k = 0;
  for (int i = 1; i < num * 9+1; i++) {
    Apex[k] = T[i];
    k += 1;
  }
  return Apex;
}

double *getCenter(const char *filename) {
  double *S;
  double *center;
  S = ReadCSV(filename);
  int num = S[4];
  center = (double *)malloc(num * 3 * sizeof(double));
  int k = 0;
  for (int i = 5; i < num * 3 + 5; i++) {
    center[k] = S[i];
    k += 1;
  }
  return center;
}
