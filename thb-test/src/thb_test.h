/* program to check if a tree is height-balanced or not. Linear time algorithm. */

#ifndef THBTEST_H_
#define THBTEST_H_
#include<stdio.h>
#include<stdlib.h>
struct node
{
  int data;
  struct node* left;
  struct node* right;
};

/* The function returns true if root is balanced else false
   The second parameter is to store the height of tree.  
   Initially, we need to pass a pointer to a location with value 
   as 0. We can also write a wrapper over this function */
int isBalanced(struct node *root, int* height);

 

#endif  /*end of THBTEST_H_ define*/
