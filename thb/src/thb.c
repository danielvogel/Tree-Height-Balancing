#include "thb.h"
#include <stdlib.h>

void balance() {
}

void flatten() {
}
//...



/* functions for tree nodes */

Node * newNode(char *data){
    
    Node* node = (struct node*) malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
 
    return node;
}

Node *newNodeWithChildren(char *data, Node *left, Node *right){
    struct node* node = newNode(data);
    node->left = left;
    
    node->right = right;
    
    
    return node;
}



/* Functions for lists */
/* source: http://perlgeek.de/de/artikel/doppelt-verkettete-listen */
ListItem * new_list(){
	struct list_item *new = (struct list_item*) malloc(sizeof(struct list_item));
	new->data  = NULL;
	new->right = new;
	new->left  = new;
	return new;
}

ListItem * insert_right(struct list_item *list, Node* data){
	struct list_item *new = (struct list_item *) malloc(sizeof(struct list_item));
	new->data        = data;
	new->left        = list;
	new->right       = list->right;
	list->right      = new;
	new->right->left = new;
	return new;
}

ListItem * delete(struct list_item *list){
	list->right->left = list->left;
	list->left->right = list->right;
	return list->left;
}