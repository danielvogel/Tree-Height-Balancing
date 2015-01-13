#ifndef THB_H
#define	THB_H

#include "namequeue.h"




typedef struct uses {
    int count;
    Node ** user;
} Uses;

ListItem *forest;

Uses * uses(ListItem * forest, char * name);

void balance(Node *root);
int flatten(Node *var, NameQueue *q);
int inUEVar(Node *var);
void rebuild(NameQueue *q, Operation *op);
Node *fold(Operation *op, Node *left, Node *right);
#endif	/* THB_H */
