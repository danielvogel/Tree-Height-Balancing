#include <stdio.h>
#include <stdlib.h>
#include "thb.h"
#include "graph.h"
#include "dependency_graph.h"


ListItem* initCode();
void printRoots(NameQueue * Roots);



int main(int argc, char** argv) {

    ListItem* forest = initCode();
    NameQueue * Roots = roots(forest);
    graph* g = GraphCreate();
    depGraph *dg;

    vertex* y = GraphAddVertex(g, "y","+", NULL);
    vertex* z = GraphAddVertex(g, "z", "*", NULL);
    vertex* t1 = GraphAddVertex(g, "t1","*", NULL);
    vertex* t2 = GraphAddVertex(g, "t2","-", NULL);
    vertex* a = GraphAddVertex(g, "a",NULL, NULL);
    vertex* b = GraphAddVertex(g, "b",NULL, NULL);
    vertex* c = GraphAddVertex(g, "c",NULL, NULL);    
    vertex* d = GraphAddVertex(g, "d",NULL, NULL);


    GraphAddEdge(g,y,t1);
    GraphAddEdge(g,z,t1);
    GraphAddEdge(g,y,t2);
    GraphAddEdge(g,z,t2);
    GraphAddEdge(g,t1,a);
    GraphAddEdge(g,t1,b);
    GraphAddEdge(g,t2,c);
    GraphAddEdge(g,t2,d);
 
    printGraph(g);

    printRoots(Roots);
    return (EXIT_SUCCESS);
}

void printRoots(NameQueue * Roots){

    NameQueue * current = Roots;
    
    do{
        printf("(%s %d)", current->name, current->precedence);
        
    } while ((current = current->next) != NULL);
   
}


ListItem* initCode() {

    Operation* add = newOp("+", 1, 1, 1);
    Operation* mul = newOp("*", 1, 1, 2);

    ListItem* forest = new_list();
    ListItem* head = forest;
    
    Node* t1 = newNodeWithChildren("t1", add,
            newNode("13"),
            newNode("a"));
    
    

    Node* t2 = newNodeWithChildren("t2", add,
            t1,
            newNode("b"));

    Node* t3 = newNodeWithChildren("t3", add,
            t2,
            newNode("4"));

    Node* t4 = newNodeWithChildren("t4", mul,
            t3,
            newNode("c"));

    Node* t5 = newNodeWithChildren("t5", mul,
            newNode("3"),
            t4);

    Node* t6 = newNodeWithChildren("t6", mul,
            newNode("d"),
            t5);

    Node* t7 = newNodeWithChildren("t7", add,
            newNode("e"),
            newNode("f"));

    Node* t8 = newNodeWithChildren("t8", add,
            t7,
            newNode("g"));

    Node* t9 = newNodeWithChildren("t9", add,
            t8,
            newNode("h"));

    Node* t10 = newNodeWithChildren("t10", mul,
            t3,
            t7);

    Node* t11 = newNodeWithChildren("t11", add,
            t3,
            t9);

    
    forest->data = t1;
    forest = insert_right(forest, t2);
    forest = insert_right(forest, t3);
    forest = insert_right(forest, t4);
    forest = insert_right(forest, t5);
    forest = insert_right(forest, t6);
    forest = insert_right(forest, t7);
    forest = insert_right(forest, t8);
    forest = insert_right(forest, t9);
    forest = insert_right(forest, t10);
    forest = insert_right(forest, t11);


    return head;
 }


