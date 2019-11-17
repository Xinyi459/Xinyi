//
//  main.c
//  HW6T3
//
//  Created by xinyi on 10/19/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

int main() {
    int d;
    char c;
    short s;
    int *p;
    int arr[2];
    
    p = &d;
    *p = 10;
    c = (char)1;
    
    p = arr;
    *(p + 1) = 5;
    p[0] = d;
    printf("%p\n",&p[0]);
    printf("%d\n",arr[0]);
    *((char *)p + 1) = c;
     printf("%p\n",&p[0]);
     printf("%d\n",p[0]);
    return 0;
}
