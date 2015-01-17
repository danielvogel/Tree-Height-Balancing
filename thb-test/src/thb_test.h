/* program to check if a tree is height-balanced or not. Linear time algorithm. */

#ifndef THBTEST_H_
#define THBTEST_H_

#include <stdio.h>
#include <stdlib.h>

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
typedef struct treeNode
{
    struct treeNode* left;
    struct treeNode* right;
    struct node *data;
}Tree;
/*
 * @brief	The function returns true if root is balanced else false
 *  			The second parameter is to store the height of tree.  
 *  			Initially, we need to pass a pointer to a location with value 
 *  			as 0. We can also write a wrapper over this function 
 *	@param[in]	*root Is the struct of the tree
 *	@param[in,out]	*height  Is the int-pointer which will be place the height of the tree
 *	@return 	1 If tree is balanced
 *				0 If tree is nor balanced	
 */
int isBalanced(Tree *root, int* height);
 

#endif  /*end of THBTEST_H_ define*/
