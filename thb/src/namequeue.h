#ifndef NAMEQUEUE_H
#define NAMEQUEUE_H

#include "codetree.h"

typedef struct name_queue {
    struct name_queue *next;
    struct name_queue *before;
    char *name;
    int precedence;
} NameQueue;


NameQueue * new_queue();
void enqueue(NameQueue *queue, char *name, int precedence);
NameQueue * dequeue(NameQueue *queue);

NameQueue * roots(ListItem *forest);
void quickSort(NameQueue * head);

#endif // NAMEQUEUE_H
