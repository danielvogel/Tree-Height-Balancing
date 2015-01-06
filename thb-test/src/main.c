/*main: testing thb */
#include "thb_test.h"

/* A binary tree node has data, pointer to left child
   and a pointer to right child */

struct node* newNode(int data)
{
    struct node* node = (struct node*)
                                malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return(node);
}


int main(){
	int height = 0;

	//construct test tree

  struct node *root = newNode(1);  
  root->left = newNode(2);
  root->right = newNode(3);
  root->left->left = newNode(4);
  root->left->right = newNode(5);
  root->right->left = newNode(6);
  root->left->left->left = newNode(7);
  root->left->left->left->left = newNode(7);

  
  if(isBalanced(root, &height))
    printf("Tree is balanced");
  else
    printf("Tree is not balanced");    
 
   getchar();
	
   return 0;
}
