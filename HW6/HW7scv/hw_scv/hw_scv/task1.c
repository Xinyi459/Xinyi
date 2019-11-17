//
//  task1.c
//  hw_scv
//
//  Created by xinyi on 11/3/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//


#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include "inputoutput.h"



int main(){
    double *A;
    A=ReadCSV("/Users/user/Documents/Xcode/Practice/HW6/HW7scv/hw_scv/hw_scv/sample.csv",100,8);
    //printf("%.13f\n",A[8]);
    
    const char* filename="testfile.csv";
    const double data[6]={1.12342,2.32342,3.334343,4.434343,5.343543,6.432346};
    const char** field_names="p1,p2,p3";
  
    size_t n_rows=2;
    size_t n_cols=3;
    WriteCSV(filename,
                 data,
          field_names,
               n_rows,
               n_cols);
    
    return 0;
}
    
    
