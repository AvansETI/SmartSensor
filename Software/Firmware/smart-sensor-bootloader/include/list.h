// MIT License

// Copyright (c) 2019 Leyxargon

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int n;              /* data field(s) */
	/* float b;
	 * char c;
	 * ... etc.
	 */
	struct node *next;  /* pointer to next element */
}Node;

Node *newNode(int ); /* physically creates a new node */
/* N.B. this function is called by other functions because does not take care
 * of inserting the Node in the list, but delegates this operation to other
 * functions, such as *Insert functions */

Node *preInsert(Node *, int ); /* inserts a new item at the top of the list */

Node *orderInsert(Node *, int ); /* inserts a new element in order, according to a key field */

Node *postInsert(Node *, int ); /* inserts a new item at the end of the list */

Node *findNode(Node *, int ); /* find a node in the list */

Node *deleteNode(Node *, int ); /* deletes a node corresponding to the inserted key */

Node *deleteList(Node *); /* deletes a list */

void printList(Node *); /* prints all the nodes in the list */

void MergeSort(Node **); /* sorting algorithm */

Node *Merge(Node *, Node *); /* merges two sorted linked lists */

void Split(Node *, Node **, Node **); /* split the nodes of the list into two sublists */

int countNodes(Node *); /* returns the number of nodes in the list */