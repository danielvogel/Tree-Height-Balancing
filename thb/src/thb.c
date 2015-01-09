#include "thb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



NameQueue * roots(ListItem *forest){
    NameQueue *queue = new_queue();

    ListItem * current = forest;
    
    do{
        current->data->rank = -1;
        
        if(current->data->op->isAssociative 
                && current->data->op->isCommunitative){
        
            Uses * use = uses(forest, current->data->name);
            int isOpForeign = 1;          
                
            if(use->count == 1){
                isOpForeign = use->user[0]->op != current->data->op;
            }

            if(use->count > 1 || (use->count == 1 && isOpForeign) 
                    || use->count == 0 /*in our case. because enviroment-code is missed.*/){               
                current->data->isRoot = 1;
                enqueue(queue, current->data->name, current->data->op->precedence);
            }
        }
    } while(NULL != (current = current->right));
    
    quickSort(queue);
    
    return queue;
}

Uses * uses(ListItem * forest, char * name){
    
    Uses * result = (Uses*) malloc(sizeof(Uses));
    ListItem * current = forest;
    int i;
    
    result->count = 0;
    //loop 1: get size
    do{
        if(!strcmp(name, current->data->left->name) 
                || !strcmp(name, current->data->right->name)){
            result->count++;
        }
        
        
    } while(NULL != (current = current->right));
    
    current = forest;
    result->user = (Node**) malloc(sizeof(Node*) * result->count);
    
    
    i = 0;
    //loop 2, put users in Uses struct
    do{
        if(!strcmp(name, current->data->left->name) 
                || !strcmp(name, current->data->right->name)){
            result->user[i++] = current->data;
        }
    } while(NULL != (current = current->right));
        
    return result;
}



// Create balanced tree from its root, Ti in "Ti <- Li Opi Ri"
void balance(Node *root) {
	if (root->rank >= 0)
	{
		return; // have already processed this tree
	}

	NameQueue *q = new_queue(); // First, flatten the tree
	root->rank = flatten(root->left, q) + flatten(root->right, q);
	rebuild(root, root->op); // Then, rebuild a balanced tree
}

int flatten(Node *var, NameQueue *q) { // Flatten computes a rank for var & builds the queue
	if (var->op == NULL) // Cannot recur further
	{
		var->rank = 0;
		enqueue(q, var->name, var->rank);
	} else if (1/* TODO var element UEVar(b)*/) { // Cannot recur past top of block
		var->rank = 1;
		enqueue(q, var->name, var->rank);
	} else if (var->isRoot == TRUE) { // New queue for new root
		balance(var); // Recur to find its rank
		enqueue(q, var->name, var->rank);
	} else { // var is Tj in jth op in block
		flatten(var->left, q); // Recur on left operand
		flatten(var->right, q); // Recur on right operand
	}

	return var->rank;
}

// check if UEVar(b) contains var
int inUEVar(Node *var) { // TODO
	return FALSE;
}

void rebuild(NameQueue *q, Operation *op) {
	//Node nl,nr;
	while(q->next != NULL && q->next->next != NULL) {
	}	
}
