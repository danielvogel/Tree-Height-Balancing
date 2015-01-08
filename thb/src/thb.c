#include "thb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


NameQueue * roots(ListItem *forest){
    NameQueue *queue = new_queue();
    
    ListItem * head = forest;
    ListItem * current = forest;
    
    do{
       
        if(current->data->op->isAssociative 
                && current->data->op->isCommunitative){
        
            int use = uses(forest, current->data->name);
            int isOpForeign = 1;

            if(use == 1){
                isOpForeign = getUser(forest, current->data->name)->op != current->data->op;
            }

            if(use > 1 || (use == 1 && isOpForeign)){               
                current->data->isRoot = 1;
                enqueue(queue, current->data->name);
            }
        }
    } while(head != (current = current->right));
    
    return queue;
}

int uses(ListItem * forest, char * name){
    int result = 0;
    
    ListItem * head = forest;
    ListItem * current = forest;
    
    do{
        if(!strcmp(name, current->data->left->name)){
            result++;
        }
        
        if(!strcmp(name, current->data->right->name)){
            result++;
        }
        
    } while(head != (current = current->right));
        
    return result;
}

Node * getUser(ListItem * forest, char * name){
    ListItem * head = forest;
    ListItem * current = forest;
    
    do{
        if(!strcmp(name, current->data->left->name) 
                || !strcmp(name, current->data->right->name)){
            return current->data;
        }

    } while(head != (current = current->right));
    
    return NULL;
}



void balance() {
}

void flatten() {
}
//...



/* functions for tree nodes */

Operation *newOp(char *sign, int com, int ass){
    Operation* op = (Operation*) malloc(sizeof(Operation));
    op->sign = sign;
    op->isAssociative = ass;
    op->isCommunitative = com;
    
    return op;
}


Node * newNode(char *data){
    
    Node* node = (Node*) malloc(sizeof(Node));
    node->name = data;
    node->left = NULL;
    node->right = NULL;
    node->op = NULL;
 
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
    new->right = new;
    new->left  = new;
    return new;
}

ListItem * insert_right(ListItem *list, Node* data){
    ListItem *new = (ListItem *) malloc(sizeof(ListItem));
    new->data        = data;
    new->left        = list;
    new->right       = list->right;
    list->right      = new;
    new->right->left = new;
    return new;
}

ListItem * delete(ListItem *list){
    
    ListItem *left =  list->left;
    list->right->left = list->left;
    list->left->right = list->right;
    
    free(list);
    
    return left;
}

NameQueue * new_queue(){
    NameQueue *new = (NameQueue*) malloc(sizeof(NameQueue));
    new->name  = NULL;
    new->next = NULL;
    new->before  = NULL;
    return new; 
}

void enqueue(NameQueue *queue, char *name){
   
    NameQueue * current = queue;
    
    while(current->next != NULL){
        current = current->next;
    }
    
    if(current->name == NULL){ //empty queue
        current->name = name;
    } else {
        NameQueue *new = new_queue();
        new->name = name;
        new->before = current;
        current->next = new;
    }
}

NameQueue * dequeue(NameQueue *queue){
    
    if(queue->next != NULL){
        queue->next->before = NULL; 
    }
    return queue->next;
}