#ifndef THB_H
#define	THB_H

#include "namequeue.h"

#define TRUE 1
#define FALSE 0


typedef struct uses {
    int count;
    Node ** user;
} Uses;



Uses * uses(ListItem * forest, char * name);

void balance(Node *root);
int flatten(Node *var, NameQueue *q);
int inUEVar(Node *var);
void rebuild(NameQueue *q, Operation *op);

#endif	/* THB_H */
