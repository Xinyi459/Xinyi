//
//  main.c
//  HW3T1
//
//  Created by xinyi on 9/29/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
int main(int argc,char *argv[])
{
    int num;
    int i;
    int n;
    int len;
    char*str=argv[1];
    char*test=".";
    n = strcspn(str,test);
    len = strlen(str);
    if(n==len)
    {
         num=atoi(str);
         if (num>0)
         {
         int *storageArray;
         storageArray =(int*)malloc((num+1)*sizeof(int));
         int i,j,k;
         for (i=0;i<=num;i++)
         {
             storageArray[i]=num-i;
         }
         for (j=0;j<=num;j++)
         {
             printf("%d ",storageArray[j] );
         }
         printf("\n");
     qsort(storageArray,num+1,sizeof(int),cmpfunc);
     for (k=0;k<=num;k++)
         {
             printf("%d ",storageArray[k] );
         }

             printf("\n");
         }
  }
}

