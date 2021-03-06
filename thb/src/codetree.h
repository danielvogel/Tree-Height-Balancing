#ifndef CODETREE_H
#define	CODETREE_H

#include <stdio.h>

#include "constants.h"

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
typedef struct treeNode
{
    struct treeNode* left;
    struct treeNode* right;
    struct node *data;
}Tree;

typedef struct operation{
    char *sign;
    bool isCommutative;
    bool isAssociative;
    int precedence;
} Operation;

typedef struct node{
    char *name;
    Operation *op;
    struct node *left;
    struct node *right;
    bool isRoot;
    int rank;
    bool isConstant;
} Node;

typedef struct list_item {
    struct list_item *left;
    struct list_item *right;
	Node *data;
	Tree *treeData;
} ListItem;


/* functions for tree nodes*/
Operation *newOp(char *sign, int com, int ass, int precedence);
Node *newNode(char *data);
Node *newNodeWithChildren(char *data, Operation *op, Node *left, Node *right);
Node *nodeByName(ListItem* forest, char * name);

/* functions for lists */
ListItem * new_list();
ListItem * insert_right(struct list_item *list, Node* data);
ListItem * insert_right_tree(struct list_item *list, Tree* data);
ListItem * delete(struct list_item *list);

/* functions for trees */
Tree *treeFromNodes(Node *parent, Node *left, Node *right);
void printTreeDataList(ListItem *l);
void printTree(Tree *t, int level);
Tree *getTreeFromList(ListItem *list);

#endif	/* CODETREE_H */
