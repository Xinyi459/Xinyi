//
//  traversal.c
//  traversal
//
//  Created by xinyi on 10/14/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "dll_alloc.h"
#include "structs.h"
#include "traversal.h"

void PrintDLLForward(ListNode* head){
    while (head->next->data!=0){
        printf("%d\n",head->data);
        head=head->next;
    }
    printf("%d\n",head->data);
}


void PrintDLLReverse(ListNode* head){
    while (head->prev->data!=0){
        printf("%d\n",head->data);
        head=head->prev;
    }
    printf("%d\n",head->data);
}

