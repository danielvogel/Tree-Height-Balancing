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
	if (DEBUG_OUTPUT) printf("Called balance() for node \"%s\".\n", root->name);
	if (root->rank >= 0)
	{
		if (DEBUG_OUTPUT) printf("Node \"%s\" is already balanced. Returning...\n", root->name);
		return; // have already processed this tree
	}
	
	NameQueue *q = new_queue(); // First, flatten the tree
	root->rank = flatten(root->left, q) + flatten(root->right, q);
	if (DEBUG_OUTPUT) printf("Set rank of node \"%s\" to %d.\n", root->name, root->rank);
	rebuild(q, root->op); // Then, rebuild a balanced tree
}

int flatten(Node *var, NameQueue *q) { // Flatten computes a rank for var & builds the queue
	if (DEBUG_OUTPUT) printf("Called flatten() for node \"%s\" in queue \"%s\".\n", var->name, q->name);
	if (var->isConstant == TRUE) // Cannot recur further
	{
		var->rank = 0;
		if (DEBUG_OUTPUT) printf("\tNode \"%s\" is a constant, set rank to 0.\n", var->name);
		enqueue(q, var->name, var->rank);
	} else if (inUEVar(var) == TRUE) { // Cannot recur past top of block
		var->rank = 1;
		if (DEBUG_OUTPUT) printf("\tNode \"%s\" is in UEVar, set rank to 1.\n", var->name);
		enqueue(q, var->name, var->rank);
	} else if (var->isRoot == TRUE) { // New queue for new root
		if (DEBUG_OUTPUT) printf("\tNode \"%s\" is a root element. Calling balance() for Node.\n", var->name);
		balance(var); // Recur to find its rank
		enqueue(q, var->name, var->rank);
	} else { // var is Tj in jth op in block
		if (DEBUG_OUTPUT) printf("\tCalling flatten for left and right part of node \"%s\".\n", var->name);
		flatten(var->left, q); // Recur on left operand
		flatten(var->right, q); // Recur on right operand
	}

	return var->rank;
}

// In tests set UEVar!
int sizeOfUEVar()
{
	int i = 0;
	UEVarQueue *element = UEVar;

	while (element != NULL)
	{
		i++;
		element = element->next;
	}

	return i;
}

UEVarQueue *getEndOfUEVar()
{
	if (DEBUG_OUTPUT) printf("Getting end of UEVar.\n");
	UEVarQueue *element = UEVar;

	while (element != NULL)
	{
		element = element->next;
	}

	return element;
}

// check if UEVar(b) contains var
bool inUEVar(Node *var) {
	if (DEBUG_OUTPUT) printf("Checking if node \"%s\" is in UEVar.\n", var->name);

	bool result = FALSE;
	UEVarQueue *element = UEVar;

	printf("Size of UEVar is %d.\n", sizeOfUEVar());

	while (result != TRUE && element != NULL)
	{
		printf("Element of UEVar is \"%s\".\n", element->name);
		if (strcmp(var->name, element->name) == 0)
		{
			result = TRUE;
		}
		element = element->next;
	}

	if (result == TRUE)
	{
		if (DEBUG_OUTPUT) printf("Node \"%s\" is in UEVar.\n", var->name);
	} else {
		if (DEBUG_OUTPUT) printf("Node \"%s\" is not in UEVar.\n", var->name);
	}

	return result;
}

void rebuild(NameQueue *q, Operation *op) {
	printf("Start rebuilding tree\n");
	printf("---------------------\n");

	Node *nl, *nr, *nt;
	while(q->next != NULL && q->next->next != NULL) {

		nl = nodeByName(forest, q->next->name);
		nr = nodeByName(forest, q->next->next->name);
		q  = q->next->next;
		
		if (DEBUG_OUTPUT)
			printf("Examining nodes '%s' and '%s' for rebuild.\n", nl->name, nr->name);
		
		if (nl->isConstant && nr->isConstant) {
			nt = fold(op, nl, nr);
			getVariableName(nt);
			if (q->next == NULL) {
				printf("root: %s --> [ %s %s %s ]\n", nt->name, nl->name, op->sign, nr->name);
				nt->rank = 0;
			} else {
				if (DEBUG_OUTPUT)
					printf("Enqueueing new node %s\n", nt->name);
				enqueue(q,nt->name,0);
				nt->rank = 0;
			}
		} else {
			if (q->next == NULL) {
				nt->isRoot = TRUE;
			} else {
				getVariableName(nt);
			}
			printf("%s <-- %s %s %s\n", nt->name, nl->name, op->sign, nr->name);
			nr->rank = nl->rank + nr->rank;
			if (q->next != NULL) {
				enqueue(q,nt->name,nr->rank);
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
    
 	if (DEBUG_OUTPUT)
 		printf("Successfully folded nodes '%s' and '%s' with operation '%s' to value '%s'.\n", left->name, right->name, op->sign, result->name);   
	return result;
}

void getVariableName(Node *node) {
	node->name = malloc(sizeof (char *) * 16);;
	sprintf(node->name, "tt%d", varTempCounter++);
	if (DEBUG_OUTPUT)
		printf("Generated new variable name: %s\n", node->name);
}

