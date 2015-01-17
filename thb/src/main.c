#include <stdio.h>
#include <stdlib.h>
#include "thb.h"
#include "graph.h"
#include "codetree.h"
#include "dependency_graph.h"


ListItem* initCode();
void printRoots(NameQueue * Roots);
ListItem* getCodeTrees(graph* dg);



int main(int argc, char** argv) {
	varTempCounter = 1;
    //forest = initCode();
    
    //graph* g = GraphCreate();
    depGraph *dg;

    /*vertex* y = GraphAddVertex(g, "y","+",0, NULL);
    vertex* z = GraphAddVertex(g, "z", "*",0, NULL);
    vertex* t1 = GraphAddVertex(g, "t1","*",0, NULL);
    vertex* t2 = GraphAddVertex(g, "t2","-", 0,NULL);
    vertex* a = GraphAddVertex(g, "a",NULL,1, NULL);
    a->isConstant= 1;
    vertex* b = GraphAddVertex(g, "b",NULL, 1,NULL);
    b->isConstant = 1;
    vertex* c = GraphAddVertex(g, "c",NULL,1, NULL);  
    c->isConstant = 1;
    vertex* d = GraphAddVertex(g, "d",NULL, 1,NULL);
    d->isConstant= 1;


    GraphAddEdge(g,y,t1);
    GraphAddEdge(g,z,t1);
    GraphAddEdge(g,y,t2);
    GraphAddEdge(g,z,t2);
    GraphAddEdge(g,t1,a);
    GraphAddEdge(g,t1,b);
    GraphAddEdge(g,t2,c);
    GraphAddEdge(g,t2,d);*/

    
    
  /*  printf("\nStarting creation of UEVar\n");
    UEVarQueue *uevarNodeA = (UEVarQueue *)malloc(sizeof(UEVarQueue));
    uevarNodeA->name = "a";
    printf("Created \"%s\"\n",uevarNodeA->name);
    UEVarQueue *uevarNodeB = (UEVarQueue *)malloc(sizeof(UEVarQueue));
    uevarNodeB->name = "b";
    printf("Created \"%s\"\n",uevarNodeB->name);
    uevarNodeA->next = uevarNodeB;
    printf("Set next from \"%s\" to \"%s\"\n",uevarNodeA->name, uevarNodeA->next->name);
    UEVarQueue *uevarNodeC = (UEVarQueue *)malloc(sizeof(UEVarQueue));
    uevarNodeC->name = "c";
    printf("Created \"%s\"\n",uevarNodeC->name);
    uevarNodeB->next = uevarNodeC;
    printf("Set next from \"%s\" to \"%s\"\n",uevarNodeB->name, uevarNodeB->next->name);
    UEVarQueue *uevarNodeD = (UEVarQueue *)malloc(sizeof(UEVarQueue));
    uevarNodeD->name = "d";
    printf("Created \"%s\"\n",uevarNodeD->name);
    uevarNodeC->next = uevarNodeD;
    printf("Set next from \"%s\" to \"%s\"\n",uevarNodeC->name, uevarNodeC->next->name);
    UEVar = uevarNodeA;
    printf("First element of UEVar is \"%s\"\n", UEVar->name);
    printf("Last element of UEVar is \"%s\"\n", UEVar->next->next->next->name);
    printf("Size of UEVar is %d\n", sizeOfUEVar());
    printf("Finished creation of UEVar\n\n");*/

    dg = parseToDependencyGraph(GRAPHS_PATH);
    
    depGraph* current = dg;
    
    do{
        if(current->g == NULL)break;
        
        printGraph(current->g);
        
    	UEVar = current->uevar;
    	if (DEBUG_OUTPUT) printf("Set UEVar, size is %d,\n", sizeOfUEVar());

        forest = getCodeTrees(current->g);

        NameQueue *Roots = roots(forest);
        Node *node;
        
        printRoots(Roots);

        while (Roots->next != NULL && (nodeByName(forest, Roots->next->name) != NULL)) {
            node = nodeByName(forest, Roots->next->name);
            if (DEBUG_OUTPUT)
                    printf("Start balancing node: %s\n", node->name);
            balance(node);
            Roots = Roots->next;
        }
    } while ((current = current->next) != NULL);
    
    return (EXIT_SUCCESS);
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
        
        if(current->operation == NULL){
            new->isConstant = current->isConstant;
        } else {
            
            if(!strcmp(current->operation , "+")){
                new->op = add;
            } else if(!strcmp(current->operation , "*")){
                new->op = mul;
            } else if(!strcmp(current->operation , "-")){
                new->op = sub;
            } else if(!strcmp(current->operation , "/")){
                new->op = div;
            } else {
                printf("%s not supported operation\n", current->operation );
                exit(1);
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
