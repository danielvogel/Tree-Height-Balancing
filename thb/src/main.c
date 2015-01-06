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
           
    struct node* t3 = newNodeWithChildren("t3", 
            newNodeWithChildren("t2", 
                    newNodeWithChildren("t1",
                        newNode("13"),
                        newNode("a")), 
                    newNode("b")),
            newNode("4"));
    
    struct node* t6 = newNodeWithChildren("t6",
            newNode("d"),
            newNodeWithChildren("t5",
                newNode("3"),
                newNodeWithChildren("t4",
                    t3,
                    newNode("c"))));
    
    struct node* t7 = newNodeWithChildren("t7",
            newNode("e"),
            newNode("f"));
    
    struct node* t10 = newNodeWithChildren("t10",
            t3, 
            t7);
    
    struct node* t11 = newNodeWithChildren("t11",
            t3,
            newNodeWithChildren("t9",
                newNodeWithChildren("t8",
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


