#include <stdlib.h>
#include <string.h>
#include "codetree.h"
#include <stdio.h>

/* functions for tree nodes */

Operation *newOp(char *sign, int com, int ass, int precedence){
    Operation* op = (Operation*) malloc(sizeof(Operation));
    op->sign = sign;
    op->isAssociative = ass;
    op->isCommutative = com;
    op->precedence = precedence;
    
    return op;
}


Node * newNode(char *data){
    
    Node* node = (Node*) malloc(sizeof(Node));
    node->name = data;
    node->left = NULL;
    node->right = NULL;
    node->op = NULL;
    node->isConstant = FALSE; // asd
    node->rank = 0;
 
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
ListItem * new_list() {
    ListItem *new  = (ListItem*) malloc(sizeof(ListItem));
    new->data  = NULL;
    new->right = NULL;
    new->left  = NULL;
    new->treeData = NULL;
    return new;
}

ListItem * insert_right(ListItem *list, Node* data){
    ListItem *new = (ListItem *) malloc(sizeof(ListItem));
    new->data        = data;
    new->left        = list;
    new->right       = list->right;
    list->right      = new;
    
    if(new->right != NULL){
        new->right->left = new;
    }

    return new;
}

ListItem * insert_right_tree(struct list_item *list, Tree* data) {
	ListItem *new = (ListItem *) malloc(sizeof(ListItem));
    new->treeData        = data;
    new->left        = list;
    new->right       = list->right;
    list->right      = new;
    
    if(new->right != NULL){
        new->right->left = new;
    }

    return new;
}

ListItem * delete(ListItem *list){
    
    ListItem *left =  list->left;
    list->right->left = list->left;
    list->left->right = list->right;
    
    free(list);
    
    return left;
}


Node * nodeByName(ListItem* forest, char * name){
    ListItem* current = forest;
    
    do{
        if(!strcmp(name, current->data->name)){
            return current->data;
        }
    } while(NULL != (current = current->right));
    
    
    return NULL;
}


Tree *treeFromNodes(Node *parent, Node *left, Node *right) 
{
	Tree *tp = (Tree*) malloc(sizeof(Tree));
	tp->data = parent;
	
	Tree *tl = (Tree*) malloc(sizeof(Tree));
	tl->data = left;
	
	Tree *tr = (Tree*) malloc(sizeof(Tree));
	tr->data = right;
	
	tp->left  = tl;
	tp->right = tr;
	
	return tp;
}

void printTreeDataList(ListItem *l) {
	while (l != NULL) {
		Tree *t = l->treeData;
		printTree(t,0);
		l = l->right;	
	}
}

void printTree(Tree *t, int level) {
	int i=0;
	for (;i<level;i++)
		printf("\t");
		
	printf("%s (%d)",t->data->name, t->data->rank);
	if (t->data->op != NULL)
		printf(" %s\n",t->data->op->sign);
	else
		printf("\n");
		
	
		
	
	if (t->left->data->name != NULL)
		printTree(t->left,level+1);
	if (t->right->data->name != NULL)
		printTree(t->right,level+1);
}

Tree *getTreeFromList(ListItem *l) {
	if(strcmp("root", l->treeData->data->name)){
		printf("Cannot build tree, first item is not root!\n");
		return NULL;
    }
    
	Tree *root = l->treeData;
	ListItem *tmp = l->right;

	while (tmp != NULL) {
		if(!strcmp(root->left->data->name, tmp->treeData->data->name)) {
			root->left = tmp->treeData;
			break;
		}
		tmp = tmp->right;
	}
	
	tmp = l->right;
	while (tmp != NULL) {
		if(!strcmp(root->right->data->name, tmp->treeData->data->name)) {
			root->right = tmp->treeData;
			break;
		}
		tmp = tmp->right;
	}
	return root;
}
