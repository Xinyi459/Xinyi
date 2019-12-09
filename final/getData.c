//
//  getData.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "getData.h"
#include "getNum.h"
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
    int m = (n - n / 4) * 3 + n / 4;
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
    int num = getT(filename);
    Apex = (double *)malloc(num * 9 * sizeof(double));
    int k = 0;
    for (int i = 0; i < num; i++) {
        for (int j = i * 10 + 1; j < i * 10 + 10; j++) {
            Apex[k] = T[j];
            k += 1;
        }
    }
    return Apex;
}

double *getCenter(const char *filename) {
    double *S;
    double *center;
    S = ReadCSV(filename);
    int num = getS(filename);
    center = (double *)malloc(num * 3 * sizeof(double));
    int k = 0;
    for (int i = 0; i < num; i++) {
        for (int j = i * 5; j < i * 5 + 3; j++) {
            center[k] = S[j];
            k += 1;
        }
    }
    return center;
}
