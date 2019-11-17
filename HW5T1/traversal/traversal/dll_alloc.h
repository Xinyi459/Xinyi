//
//  dll_alloc.h
//  traversal
//
//  Created by xinyi on 10/14/19.
//  Copyright © 2019 Xinyi. All rights reserved.
//

#ifndef DLL_ALLOC_H
#define DLL_ALLOC_H

#include "structs.h"

// Allocates memory for count nodes and links them together into a
// circular, doubly-linked list
void CreateDLL(ListNode** head, int count);

// Frees memory for all count nodes in a circular, doubly-linked list
void FreeDLL(ListNode* head, int count);

#endif
