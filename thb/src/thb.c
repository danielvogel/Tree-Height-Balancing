#include "thb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


NameQueue * roots(ListItem *forest){
    NameQueue *queue = new_queue();

    ListItem * current = forest;
    
    do{
        current->data->rank = -1;
        
        if(current->data->op && current->data->op->isAssociative 
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
        if(current->data->op){
            if(!strcmp(name, current->data->left->name) 
                    || !strcmp(name, current->data->right->name)){
                result->count++;
            }
        }
        
        
    } while(NULL != (current = current->right));
    
    current = forest;
    result->user = (Node**) malloc(sizeof(Node*) * result->count);
    
    
    i = 0;
    //loop 2, put users in Uses struct
    do{
         if(current->data->op){
            if(!strcmp(name, current->data->left->name) 
                    || !strcmp(name, current->data->right->name)){
                result->user[i++] = current->data;
            }
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
	rebuild(q, root->op); // Then, rebuild a balanced tree
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
	printf("Start rebuilding tree");

	Node *nl, *nr, *nt;
	//while(q->next != NULL && q->next->next != NULL) {
	if(1) {
		/*q = q->next->next->next;
		nl = nodeByName(forest, q->next->name);
		nr = nodeByName(forest, q->next->next->name);
		
		printf("Examining nodes '%s' and '%s' for rebuild.", nl->name, nr->name);*/
		
		nl = newNode("5");
		nr = newNode("18");
		nl->isConstant = TRUE;
		nr->isConstant = TRUE;
		op->sign = "*";
		if (nl->isConstant && nr->isConstant) {
			nt = fold(op, nl, nr);
			if (q->next == NULL) {
				printf("root <-- %s\n", nt->name);
				nt->rank = 0;
			} else {
				enqueue(q,nt->name,0);
				nt->rank = 0;
			}
		} else {
			if (q->next == NULL) {
				nt->isRoot = TRUE;
			} else {
				nt->name = ""; // --> TODO generate new name (e.g. starting from t0... with global var)
			}
		}		
	}	
}


Node *fold(Operation *op, Node *left, Node *right) {
	char *endPtr;
	Node *result = newNode("");
	result->name = malloc(sizeof (char *) * 16);
	result->rank = 0;
	
	int leftOp  = strtol(left->name, &endPtr, 10);
	int rightOp = strtol(right->name, &endPtr, 10);
	int intRes;
	
	if(!strcmp(op->sign, "+")) {
		intRes = leftOp + rightOp;
    } else if(!strcmp(op->sign, "*")) {
		intRes = leftOp * rightOp;
    } else if(!strcmp(op->sign, "-")) {
        intRes = leftOp - rightOp;
    } else if(!strcmp(op->sign, "/")) {
        intRes = leftOp / rightOp;
    }
       
    sprintf(result->name, "%d", intRes);
    
 	printf("Successfully folded nodes '%s' and '%s' with operation '%s' to value '%s'.\n", left->name, right->name, op->sign, result->name);   
	return result;
}

