//
//  main.c
//  459Final
//
//  Created by xinyi on 11/6/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <GLUT/GLUT.h>
#include "inputoutput.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[]){
    double *A;
    double *Apex;
    int *ID;
    A=ReadCSV("/Users/user/Documents/Xcode/Practice/459Final/459Final/mesh.csv");
    int len=Getlen("/Users/user/Documents/Xcode/Practice/459Final/459Final/mesh.csv");
    //data of triangles
    //get apex of each mesh
    Apex=(double*)malloc(len*9/4*sizeof(double));
    int num=len/4;
    int k=0;
    for(int i =0;i<num;i++){
        for(int j =i*10+1;j<i*10+10;j++){
            Apex[k]=A[j];
            k+=1;
        }
    }
    for(int i=0;i<9;i++){
        //printf("%f\n",Apex[i]);
    }
    //the ID array
    ID=(int*)malloc(len/4*sizeof(int));
    for(int i=0;i<len/4;i++){
        ID[i]=i+1;
    }
    for(int i=0;i<len/4;i++){
        //printf("%d ",ID[i]);
    }
    
    
    //data of spheres
    double *S;
    double *center;
    int *IDs;
    S=ReadCSV("/Users/user/Documents/Xcode/Practice/459Final/459Final/sphere.csv");
    int lens=Getlen("/Users/user/Documents/Xcode/Practice/459Final/459Final/sphere.csv");
    //get center data
    center=(double*)malloc(lens*sizeof(double));
    int nums=lens/3;
    int rows=0;
    for(int i=0;i<nums;i++){
        int cols=0;
        for(int j=i*5;j<i*5+3;j++){
            center[rows*3+cols]=S[j];
            cols+=1;
        }
        rows+=1;
    }
    for(int i=0;i<6;i++){
        //printf("%f\n",center[i]);
    }
    //get r
    int r=S[3];
    //the ID array
    IDs=(int*)malloc(lens/3*sizeof(int));
    for(int i=0;i<len/3;i++){
        IDs[i]=i+1;
    }
    for(int i=0;i<len/3;i++){
        //printf("%d ",IDs[i]);
    }
 
    double *plane=Getplane(Apex,len);
    for (int i=0;i<8;i++){
        //printf("%f\n",plane[i]);
    }
    
    double *centerP=CenterToP(center,plane,len,lens);
    for(int i=0;i<12;i++){
        printf("%f\n",centerP[i]);
    }
  
   
    
    
    
    
    
    
}
