//
//  main.c
//  HW3
//
//  Created by xinyi on 9/29/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "sort.h"

int main(int argc,char *argv[])
{
    srand((unsigned int)time(NULL));
    int storageArray[20];
    for (int i=0;i<=19;i++)
    {
        storageArray[i]=rand()%100+1;
        printf("%d ",storageArray[i]);
    }
    printf("\n");
    sort(storageArray,(20));
    for (int k=0;k<=19;k++)
    {
        printf("%d ",storageArray[k]);
    }
    printf("\n");
}
