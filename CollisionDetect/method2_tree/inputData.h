#ifndef inputData_H
#define inputData_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void writeStrToFile(FILE* f, char* str);
double* ReadCSV1(FILE* f1, int* n_rows, int n_cols, int kk);
double* ReadCSV2(FILE* f1, double *r, int* n_rows, int n_cols);
void WriteCSV(FILE* f2, double* data, int rows, int cols);
#endif
