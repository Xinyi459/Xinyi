//
//  inputoutput.c
//  hw_scv
//
//  Created by xinyi on 11/3/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//


#include "inputoutput.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


double* ReadCSV(const char* filename, size_t* n_rows, size_t *n_cols){
    FILE*fp;
    fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "failed to open file for reading\n");
        exit(1);
    }
    char line[(int)n_rows*(int)n_cols];
    char *value;
    int i =1;
    double fvalue;
    double A[(int)n_rows*(int)n_cols];
    //put values in csv file into array A
    while (!feof(fp)&&i<=((int)n_rows)+1){
        fgets(line,sizeof(double)*(int)n_rows*(int)n_cols,fp);
        if(i!=1){
            int j=0;
            value=strtok(line, ",");
            while(value!=NULL){
                fvalue = atof(value);
                A[(i-2)*(int)n_cols+j]=fvalue;
                j+=1;
                value =strtok( NULL, "," );
            }
        }
        i+=1;
    }
    fclose (fp);
    return A;
}


void WriteCSV(const char* filename,
              const double* data,
              const char** field_names,
              size_t n_rows,
              size_t n_cols){
    FILE *fp;
    int i,j;
    fp=fopen("/Users/user/Documents/Xcode/Practice/HW6/HW7scv/hw_scv/hw_scv/test.csv","w+");
    fprintf(fp,"%s\n",field_names);
    for(i=0;i<(int)n_rows;i++){
        for(j=0;j<(int)n_cols;j++){
            if(j==((int)n_cols-1)){
                fprintf(fp,"%.12f",data[i*(int)n_rows+j]);
            }
            else{
                fprintf(fp,"%.12f,",data[i*(int)n_rows+j]);
            }
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

