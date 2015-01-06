#ifndef THB_H
#define	THB_H

struct node{
    int data;
    struct node* left;
    struct node* right;
};


struct node* createTree();
struct node* newNode(int data);

#endif	/* THB_H */

