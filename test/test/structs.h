//
//  structs.h
//  test
//
//  Created by xinyi on 10/9/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#ifndef structs_h
#define structs_h
struct A {
    int i;
    char c[20];
    double d;
};

struct B {
    int i;
    double d;
    char c;
};

typedef struct ListNode {
    int data;               // This node's data
    struct ListNode* next;  // Pointer to the next node in the list
    struct ListNode* prev;  // pointer to the previous node in the list
} ListNode;


#endif /* structs_h */
