#ifndef GRAPH_H
#define GRAPH_H

/**
  A graph is yet another data structure that you can use to store information. 
  Unlike trees, which have a strict hierarchical structure, graphs are more flexible. 
  As mentioned, graphs are pretty generic data structures in that they can be used to represent lots of things. 
  Thus, exactly what operations we'll want for a graph will depend on what we want to do with it.
*/
#include <stdlib.h>
#include <malloc.h>


typedef struct vertexTag {
  char* element;    // vertex name
  char* operation;  // operation (it is a constant if NULL)
  int isConstant;
  int isVariable;
  int isVisited;
  struct edgeTag* edge;
  struct vertexTag *next;
} vertex;

typedef struct edgeTag {
    struct vertexTag *connectsTo;
    struct edgeTag *next;
 } edge;

typedef struct graphTag{
  vertex *vertices;
}graph;


/*functions protoype*/

/*
Add a vertex to the graph with a name, and optionally some data
*/
vertex* GraphAddVertex(graph*, char*,char*, int, vertex* );

/*
Create a directed edge between vertex1 (source) and vertex2(destination). 
*/
void GraphAddEdge(graph*, vertex*, vertex*);

/*
Create an empty graph
*/
graph* GraphCreate();

/*
Delete a graph
*/
void GraphDestroy(graph*);


void printGraph(graph*);

/*
Insert a new edge 
*/
void insertEdge(edge* head, vertex* v1);


vertex *GraphGetVertexByNameAndOperation(graph*, char* , char* );
vertex *GraphGetVertexByName(graph* , char* );
#endif /*GRAPH_H_*/ 
