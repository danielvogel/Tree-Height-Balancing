#include <stdio.h>
#include <stdlib.h>
#include "thb.h"
#include "graph.h"
#include "codetree.h"
#include "dependency_graph.h"
#include "globals.h"
#include "thb_test.h"

ListItem* initCode();
void printRoots(NameQueue * Roots);
ListItem* getCodeTrees(graph* dg);
void isTreeBalanced(ListItem *l) ;


int main(int argc, char** argv) {
	int dgCounter = 1;
	varTempCounter = 1;

    depGraph *dg;

    dg = parseToDependencyGraph(GRAPHS_PATH);
    
    depGraph* current = dg;
    
    do{
        if(current->g == NULL)break;
        
        printf("##########################################\n");
		printf("# STAR PROCESSING DEPENDENCY GRAPH no.%d #\n",dgCounter++);
		printf("##########################################\n");
        
        resultTrees = new_list();
        
        printGraph(current->g);
        
    	UEVar = current->uevar;
    	if (DEBUG_OUTPUT) printf("Set UEVar, size is %d,\n", sizeOfUEVar());

        forest = getCodeTrees(current->g);

        NameQueue *Roots = roots(forest);
        Node *node;
       
        if(Roots->name == NULL){
            
            printf("Result Phase 1:\nNo root found!\n");
            continue;
        } 
        
        printRoots(Roots);

        while (Roots != NULL && (nodeByName(forest, Roots->name) != NULL)) {
            node = nodeByName(forest, Roots->name);
            if (DEBUG_OUTPUT) printf("Start balancing node: %s\n", node->name);
            balance(node);
            Roots = Roots->next;
        }
        printf("THE RESULT OF TREE HEIGHT BALANCING:\n");
        printTreeDataList(resultTrees->right);
        printf("Is the tree height-balanced?\n");
        isTreeBalanced(resultTrees->right);

        
    } while ((current = current->next) != NULL);
    
    return (EXIT_SUCCESS);
}


void isTreeBalanced(ListItem *l) 
{
    int height = 0;
	while (l != NULL) {
		Tree *t = l->treeData;
		if(isBalanced(t,&height))
			printf("Tree %s (%d) is balanced\n", t->data->name, t->data->rank);
		else
    		printf("Tree %s (%d) is not balanced\n", t->data->name, t->data->rank);   
        l = l->right;	
	}
}
void printRoots(NameQueue * Roots){

    NameQueue * current = Roots;
    
    printf("\nResult Phase 1:\n");
    
    do{
        printf("(%s %d)", current->name, current->precedence);
        
    } while ((current = current->next) != NULL);
   
    printf("\n\n");
}



ListItem* getCodeTrees(graph* dg){
    
    Operation* add = newOp("+", 1, 1, 1);
    Operation* mul = newOp("*", 1, 1, 2);
    Operation* sub = newOp("-", 0, 0, 1);
    Operation* div = newOp("/", 0, 0, 2);

    ListItem* forest = new_list();
    ListItem* currForest = forest;
    
    vertex* current = dg->vertices;
    
    do {
        Node * new = newNode(current->element);
        
        new->isConstant = current->isConstant;

        if(current->operation != NULL){
        
            if(!strcmp(current->operation , "+")){
                new->op = add;
            } else if(!strcmp(current->operation , "*")){
                new->op = mul;
            } else if(!strcmp(current->operation , "-")){
                new->op = sub;
            } else if(!strcmp(current->operation , "/")){
                new->op = div;
            } else if (strcmp(current->operation , VERTEX_VAR) && strcmp(current->operation , VERTEX_CONST)){
                printf("'%s': not supported operation\n", current->operation );
                exit(1);
            } else {
                current->operation = NULL;
            }
        }
        
        currForest = insert_right(currForest, new);
    } while((current = current->next) != NULL);
    
    forest = forest->right;
    current = dg->vertices;
    
    do {
        Node* currNode = nodeByName(forest, current->element);
        
        if(current->operation != NULL){
            if(!current->edge->next || !current->edge->next->next){
                printf("%s: operation need exactly two operands\n", current->operation );
                exit(1);
            }
            currNode->left = nodeByName(forest, current->edge->next->connectsTo->element);
            currNode->right = nodeByName(forest, current->edge->next->next->connectsTo->element);
               
        }
    } while((current = current->next) != NULL);
    
    return forest;
}
