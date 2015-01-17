#include "namequeue.h"
#include <stdlib.h>
#include<string.h>


NameQueue * new_queue(){
    NameQueue *new = (NameQueue*) malloc(sizeof(NameQueue));
    new->name  = NULL;
    new->next = NULL;
    new->before  = NULL;
    return new; 
}

void enqueue(NameQueue *queue, char *name, int precedence){
   
    NameQueue * current = queue;
    
    while(current->next != NULL){
        current = current->next;
    }
    
    if(current->name == NULL){ //empty queue
        current->name = name;
        current->precedence = precedence;
    } else {
        NameQueue *new = new_queue();
        new->name = name;
        new->before = current;
        current->next = new;
        new->precedence = precedence;
    }
}

NameQueue * dequeue(NameQueue *queue){
    
    if(queue->next != NULL){
        queue->next->before = NULL; 
    }
    return queue->next;
}








/* quicksort for NameQueue 
 source: http://www.geeksforgeeks.org/quicksort-for-linked-list/ */
void swap ( int * p_a, int * p_b, char ** n_a, char ** n_b )
{  
    int  p_t = *p_a;
    *p_a = *p_b;
    *p_b = p_t; 
    
    char * n_t = *n_a;
    *n_a = *n_b;
    *n_b = n_t;
}
 
NameQueue *lastNode(NameQueue *root)
{
    while (root && root->next)
        root = root->next;
    return root;
}
 
NameQueue * partition(NameQueue * l, NameQueue * h)
{
    // set pivot as h element
    int x  = h->precedence;
 
    // similar to i = l-1 for array implementation
    NameQueue * i = l->before;
    NameQueue *j = l;
    
    while ( j != h )
    {
        if (j->precedence <= x)
        {
            // Similar to i++ for array
            i = (i == NULL)? l : i->next;
 
            swap(&(i->precedence), &(j->precedence),
                    &(i->name), &(j->name));
        }
        j = j->next;
    }
    i = (i == NULL)? l : i->next; // Similar to i++
    swap(&(i->precedence), &(h->precedence),
                &(i->name), &(h->name));
    return i;
}
 
void _quickSort(NameQueue *  l, NameQueue * h)
{
    if (h != NULL && l != h && l != h->next)
    {
        NameQueue *p = partition(l, h);
        _quickSort(l, p->before);
        _quickSort(p->next, h);
    }
}
 
void quickSort(NameQueue * head)
{
    NameQueue * h = lastNode(head);
 
    _quickSort(head, h);
}

void printQueue(NameQueue *q) {
	if (q == NULL) {
		printf("<empty>");
		return;
	}
	
	char out[1024];
	char intBuffer[15];
    strcpy(out,"[");
    
    while(q->next != NULL)
    {
		Node *n = nodeByName(forest,q->name);
    	sprintf(intBuffer, "%d", n->rank);
    
    	strcat(out,"<");
    	strcat(out,n->name);
    	strcat(out,",");
    	strcat(out,intBuffer);
    	strcat(out,">");
        q = q->next;
    }
    strcat(out,"]\n");
    printf("%s",out);
}
