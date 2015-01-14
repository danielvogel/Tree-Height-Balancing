#ifndef THB_H
#define	THB_H

#include "namequeue.h"

typedef struct uses {
    int count;
    Node ** user;
} Uses;

ListItem *forest;
int varTempCounter;

typedef struct UEVar_queue {
    struct UEVar_queue *next;
    Node *node;
} UEVarQueue;

UEVarQueue *UEVar;

Uses * uses(ListItem * forest, char * name);
void balance(Node *root);
int flatten(Node *var, NameQueue *q);
void setUEVAR(UEVarQueue *queue);
bool cmpNode(Node *node1, Node *node2);
bool cmpOp(Operation *op1, Operation *op2);
int inUEVar(Node *var);
void rebuild(NameQueue *q, Operation *op);
Node *fold(Operation *op, Node *left, Node *right);
char *getVariableName(void);
#endif	/* THB_H */
