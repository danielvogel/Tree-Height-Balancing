#ifndef THB_H
#define	THB_H

typedef struct operation{
    char *sign;
    int isCommunitative;
    int isAssociative;
} Operation;

typedef struct Node{
    char *data;
    Operation *op;
    struct Node *left;
    struct Node *right;
    
} Node;


typedef struct list_item {
    struct list_item *left;
    struct list_item *right;
    Node *data;
} ListItem;


/* functions for tree nodes*/
Operation *newOp(char *sign, int com, int ass);
Node *newNode(char *data);
Node *newNodeWithChildren(char *data, Operation *op, Node *left, Node *right);

/* functions for lists */
ListItem * new_list();
ListItem * insert_right(struct list_item *list, Node* data);
ListItem * delete(struct list_item *list);




#endif	/* THB_H */
