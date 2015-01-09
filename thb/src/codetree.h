#ifndef CODETREE_H
#define	CODETREE_H

#include "constants.h"

typedef struct operation{
    char *sign;
    bool isCommunitative;
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
} ListItem;



/* functions for tree nodes*/
Operation *newOp(char *sign, int com, int ass, int precedence);
Node *newNode(char *data);
Node *newNodeWithChildren(char *data, Operation *op, Node *left, Node *right);

/* functions for lists */
ListItem * new_list();
ListItem * insert_right(struct list_item *list, Node* data);
ListItem * delete(struct list_item *list);

Node *nodeByName(ListItem* forest, char * name);

#endif	/* CODETREE_H */
