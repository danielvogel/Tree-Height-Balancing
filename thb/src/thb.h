#ifndef THB_H
#define	THB_H

typedef struct operation{
    char *sign;
    int isCommunitative;
    int isAssociative;
} Operation;

typedef struct Node{
    char *name;
    Operation *op;
    struct Node *left;
    struct Node *right;
    int isRoot;
} Node;


typedef struct list_item {
    struct list_item *left;
    struct list_item *right;
    Node *data;
} ListItem;

typedef struct name_queue {
    struct name_queue *next;
    struct name_queue *before;
    char *name;
    int precedence;
} NameQueue;


typedef struct vertexTag {
 char* element;
 int isVisited;
 struct edgeTag {
 	struct vertexTag *connectsTo;
 	struct edgeTag *next;
  } *edge;
 struct vertexTag *next;
} vertex;


typedef struct graphTag{
    vertex *vertices;
}graph;

/* functions for tree nodes*/
Operation *newOp(char *sign, int com, int ass);
Node *newNode(char *data);
Node *newNodeWithChildren(char *data, Operation *op, Node *left, Node *right);

/* functions for lists */
ListItem * new_list();
ListItem * insert_right(struct list_item *list, Node* data);
ListItem * delete(struct list_item *list);

NameQueue * new_queue();
void enqueue(NameQueue *queue, char *name);
NameQueue * dequeue(NameQueue *queue);


NameQueue * roots(ListItem *forest);
int uses(ListItem * forest, char * name);
Node * getUser(ListItem * forest, char * name);
#endif	/* THB_H */
