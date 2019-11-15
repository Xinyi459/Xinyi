//
//  getNum.c
//  459FinalProject
//
//  Created by xinyi on 11/15/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "getNum.h"

int getT(const char *filename){
    FILE *fp;
    fp = fopen(filename, "r");
    char *line;
    char buffer[1024];
    int n=0;
    while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL) {
        n+=1;
    }
    n=n/4;
    fclose(fp);
    return n;
}

int getS(const char *filename){
    FILE *fp;
    fp = fopen(filename, "r");
    char *line;
    char buffer[1024];
    int n=0;
    while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL) {
        n+=1;
    }
    n=n/3;
    fclose(fp);
    return n;
}
