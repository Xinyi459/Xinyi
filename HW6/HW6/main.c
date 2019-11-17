//
//  main.c
//  HW6
//
//  Created by xinyi on 10/19/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>

#define N 25

int main(int argc, char* argv[]) {
    printf("Hello world!!!!\n");
    
    for (size_t i = 0; i < N; i++) {
        printf("%zu ", i+1);
    }
    printf("\n");
    
    size_t sum = 0;
    for (size_t i = 0; i < N; i++) {
        sum += i;
    }
    printf("Sum: %zu\n", sum);
    
    int accumulate = 0;
    for(int i = 0; i < N; i++) {
        if (i % 2) {
            accumulate += i;
        } else {
            accumulate -= i;
        }
    }
    
    printf("Accumulate: %d\n", accumulate);
    
    return 0;
}
