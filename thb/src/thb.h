#ifndef THB_H
#define	THB_H

#include "codetree.h"
#include "namequeue.h"


typedef struct uses {
    int count;
    Node ** user;
} Uses;



Uses * uses(ListItem * forest, char * name);



#endif	/* THB_H */
