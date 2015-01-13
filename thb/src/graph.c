#include "graph.h"

graph* GraphCreate()
{
	graph* g = (graph*)malloc(sizeof(graph));
	g->vertices = NULL;

	return g;
}

vertex *GraphGetVertexByName(graph* g, char* sVertex)
{
	vertex *nVertex = g->vertices;		// get the first vertex

	while(nVertex != NULL ){
		if(strcmp(nVertex->element,sVertex)==0)
			return nVertex;
		nVertex = nVertex->next;	
	}

	return NULL;		
}

vertex *GraphGetVertexByNameAndOperation(graph* g, char* sVertex, char* operation)
{
	vertex *nVertex = g->vertices;		// get the first vertex

	while(nVertex != NULL ){
		if((strcmp(nVertex->element,sVertex)==0) && strcmp(nVertex,operation)==0)
			return nVertex;
		nVertex = nVertex->next;	
	}

	return NULL;		
}

vertex* GraphAddVertex(graph* Graph, char* element, char* operation, int isConstant, vertex* nextVertex)
{
	vertex *nVertex = Graph->vertices;		// get the first vertex
	vertex *v = (vertex*)malloc(sizeof(vertex));

	v->element= element;
	if(isConstant)
		v->operation = NULL;
	else
		v->operation = operation;
	v->isConstant = isConstant;
	v->isVisited = 0;
	v->next = nextVertex;
	v->edge = (edge*)malloc(sizeof(edge));

	if(Graph->vertices == NULL){
		Graph->vertices = v;
		return Graph->vertices;
	}
	else{
		while(nVertex->next != NULL)
			nVertex = nVertex->next;	
		nVertex->next = v;
		return nVertex->next;
	}
	return v;
}	

void insertEdge(edge* head, vertex* v1)
{
	edge* current = head;

    while (current->next != NULL) 
        current = current->next;
    
    /* now we can add a new variable */
    current->next = malloc(sizeof(edge));
    current->next->connectsTo = v1;
    current->next->next = NULL;
}

void GraphAddEdge(graph* Graph, vertex* vertex1, vertex* vertex2)
{
	vertex* v = Graph->vertices;

	edge * e = (edge*)malloc(sizeof(edge));
	e->next = NULL;
	e->connectsTo = vertex2;

	if(v != NULL){
		// durchlaufe die Struktur vertikal und suche mir den Knoten (vertex)
		while(v != vertex1)
			v = v->next;
		
		//austritt, sobald Knoten gefunden ist. v ist jetzt aktueller Knoten
		insertEdge(v->edge,vertex2);
	}
}


void printGraph(graph* Graph)
{
	vertex *v = Graph->vertices;		//get first vertex and iterate the through the graph
	edge* e = v->edge;
	printf("Print graph\n");

	while(v != NULL){ //compare end of vertical list (vertex)
		printf(" %s ",v->element);	// this is the vertex 
		while(e->next  != NULL){ //compare end of horizontal list (edge)
			printf(" --> [");
			printf(" %s ",e->next->connectsTo->element);
			printf("( %s ) ",e->next->connectsTo->operation);	
			printf("]");
			e = e->next;	// get next edge 
		}
		printf("\n");
		v = v->next;	// vertex behind
		if(v != NULL)
			e = v->edge;	// vertexs edge list
	}
	printf("\n");
}