#ifndef THB_H
#define	THB_H

typedef struct node{
    char *data;
    struct node *left;
    struct node *right;
    int isRoot;
} Node;


typedef struct list_item {
    struct list_item *left;
    struct list_item *right;
    Node *data;
} ListItem;


/* functions for tree nodes*/
Node *newNode(char *data);
Node *newNodeWithChildren(char *data, Node *left, Node *right);

/* functions for lists */
ListItem * new_list();
ListItem * insert_right(struct list_item *list, Node* data);
ListItem * delete(struct list_item *list);




#endif	/* THB_H */
