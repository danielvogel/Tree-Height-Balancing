#include <stdlib.h>
#include <string.h>
#include "codetree.h"


/* functions for tree nodes */

Operation *newOp(char *sign, int com, int ass, int precedence){
    Operation* op = (Operation*) malloc(sizeof(Operation));
    op->sign = sign;
    op->isAssociative = ass;
    op->isCommunitative = com;
    op->precedence = precedence;
    
    return op;
}


Node * newNode(char *data){
    
    Node* node = (Node*) malloc(sizeof(Node));
    node->name = data;
    node->left = NULL;
    node->right = NULL;
    node->op = NULL;
    node->isConstant = FALSE; // asd
    node->rank = 0;
 
    return node;
}

Node *newNodeWithChildren(char *data, Operation *op, Node *left, Node *right){
    Node* node = newNode(data);
    node->left = left;
    node->right = right;
    node->op = op;
    
    return node;
}



/* Functions for lists */
/* source: http://perlgeek.de/de/artikel/doppelt-verkettete-listen */
ListItem * new_list(){
    ListItem *new = (ListItem*) malloc(sizeof(ListItem));
    new->data  = NULL;
    new->right = NULL;
    new->left  = NULL;
    return new;
}

ListItem * insert_right(ListItem *list, Node* data){
    ListItem *new = (ListItem *) malloc(sizeof(ListItem));
    new->data        = data;
    new->left        = list;
    new->right       = list->right;
    list->right      = new;
    
    if(new->right != NULL){
        new->right->left = new;
    }

    return new;
}

ListItem * delete(ListItem *list){
    
    ListItem *left =  list->left;
    list->right->left = list->left;
    list->left->right = list->right;
    
    free(list);
    
    return left;
}


Node * nodeByName(ListItem* forest, char * name){
    ListItem* current = forest;
    
    do{
        if(!strcmp(name, current->data->name)){
            return current->data;
        }
    } while(NULL != (current = current->right));
    
    return NULL;
}


