//
//  sort.c
//  HW3
//
//  Created by xinyi on 9/29/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include "sort.h"
void sort(int* A, size_t n_elements)
{
    for (int i=0;i<=(n_elements-1);i++)
    {
        for (int j=i;j<=(n_elements-1);j++)
        {
            if (A[i]>A[j])
            {
                int t =A[i];
                A[i]=A[j];
                A[j]=t;
            }
        }
    }
}
