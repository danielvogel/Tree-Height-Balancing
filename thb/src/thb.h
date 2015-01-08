#ifndef THB_H
#define	THB_H

#include "codetree.h"

typedef struct name_queue {
    struct name_queue *next;
    struct name_queue *before;
    char *name;
    int precedence;
} NameQueue;


typedef struct uses {
    int count;
    Node ** user;
} Uses;


NameQueue * new_queue();
void enqueue(NameQueue *queue, char *name, int precedence);
NameQueue * dequeue(NameQueue *queue);

NameQueue * roots(ListItem *forest);
Uses * uses(ListItem * forest, char * name);


void quickSort(NameQueue * head);

#endif	/* THB_H */
