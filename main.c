#include <stdio.h>
#include <stdlib.h>
#include "thb.h"


int main(int argc, char** argv) {
    
    struct node* root = createTree();
    
    
    return (EXIT_SUCCESS);
}



struct node* createTree(){
    
    struct node* root =  newNode(1);
    
    //TODO give root some leafs
    
    return root;
}


struct node* newNode(int data){
    
    struct node* node = (struct node*) malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return node;
}