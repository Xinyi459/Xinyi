//
//  main.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getData.h"
#include "getNum.h"

int main(int argc, const char * argv[]) {
    double *mesh;
    mesh=ReadCSV("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/mesh.csv");
    double *sphere;
    sphere=ReadCSV("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/sphere.csv");
    int n=getS("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/sphere.csv");
    double *Apex=getApex("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/mesh.csv");
    double *Center=getCenter("/Users/user/Documents/Xcode/Practice/459FinalProject/459FinalProject/sphere.csv");
    
    
}
