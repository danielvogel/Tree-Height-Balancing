#include <stdio.h>
#include <stdlib.h>
#include "thb.h"


void print_all(ListItem* list);
ListItem* initTrees();


int main(int argc, char** argv) {
    
    ListItem* forest = initTrees();
    
    print_all(forest);
    return (EXIT_SUCCESS);
}



void print_all(ListItem* list){
	ListItem *head = list;
	ListItem *current = list;
	printf("%s ", head->data->data);
	while (head != (current = current->right)){
		printf("%s ", current->data->data);
	}
	printf("\n");
}

ListItem* initTrees(){
           
    Operation* add = newOp("+", 1, 1);
    Operation* mul = newOp("*", 1, 1);
    
    Node* t3 = newNodeWithChildren("t3", add,
            newNodeWithChildren("t2", add, 
                    newNodeWithChildren("t1", add,
                        newNode("13"),
                        newNode("a")), 
                    newNode("b")),
            newNode("4"));
    
    Node* t6 = newNodeWithChildren("t6", mul,
            newNode("d"),
            newNodeWithChildren("t5", mul,
                newNode("3"),
                newNodeWithChildren("t4", mul,
                    t3,
                    newNode("c"))));
    
    Node* t7 = newNodeWithChildren("t7", add,
            newNode("e"),
            newNode("f"));
    
    Node* t10 = newNodeWithChildren("t10", mul,
            t3, 
            t7);
    
    Node* t11 = newNodeWithChildren("t11", add,
            t3,
            newNodeWithChildren("t9", add,
                newNodeWithChildren("t8", add,
                    t7,
                    newNode("g")),
                newNode("h"))); 
    
    ListItem* forest = new_list();
    forest->data = t6;
    
    forest = insert_right(
            insert_right(
                insert_right(
                    forest, t7),
                t10),
            t11);
    
    return forest;
}


