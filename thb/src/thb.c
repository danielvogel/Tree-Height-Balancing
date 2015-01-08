#include "thb.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



NameQueue * roots(ListItem *forest){
    NameQueue *queue = new_queue();

    ListItem * current = forest;
    
    do{
        current->data->rank = -1;
        
        if(current->data->op->isAssociative 
                && current->data->op->isCommunitative){
        
            Uses * use = uses(forest, current->data->name);
            int isOpForeign = 1;          
                
            if(use->count == 1){
                isOpForeign = use->user[0]->op != current->data->op;
            }

            if(use->count > 1 || (use->count == 1 && isOpForeign) 
                    || use->count == 0 /*in our case. because enviroment-code is missed.*/){               
                current->data->isRoot = 1;
                enqueue(queue, current->data->name, current->data->op->precedence);
            }
        }
    } while(NULL != (current = current->right));
    
    quickSort(queue);
    
    return queue;
}

Uses * uses(ListItem * forest, char * name){
    
    Uses * result = (Uses*) malloc(sizeof(Uses));
    ListItem * current = forest;
    int i;
    
    result->count = 0;
    //loop 1: get size
    do{
        if(!strcmp(name, current->data->left->name) 
                || !strcmp(name, current->data->right->name)){
            result->count++;
        }
        
        
    } while(NULL != (current = current->right));
    
    current = forest;
    result->user = (Node**) malloc(sizeof(Node*) * result->count);
    
    
    i = 0;
    //loop 2, put users in Uses struct
    do{
        if(!strcmp(name, current->data->left->name) 
                || !strcmp(name, current->data->right->name)){
            result->user[i++] = current->data;
        }
    } while(NULL != (current = current->right));
        
    return result;
}



void balance() {
}

void flatten() {
}
//...





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