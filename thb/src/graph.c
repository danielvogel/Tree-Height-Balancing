#include "graph.h"

graph* GraphCreate()
{
	graph* g = (graph*)malloc(sizeof(graph));
	g->vertices = NULL;

	return g;
}

vertex* GraphAddVertex(graph* Graph, char* element, vertex* nextVertex)
{
	vertex *nVertex = Graph->vertices;		// get the first vertex
	vertex *v = (vertex*)malloc(sizeof(vertex));

	v->element= element;
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
		//printGraph(Graph);
	}
}


void printGraph(graph* Graph)
{
	vertex *v = Graph->vertices;		//get first vertex and iterate the through the graph
	edge* e = v->edge;


	while(v != NULL){ //compare end of vertical list (vertex)
		printf(" %s ",v->element);	// this is the vertex 
		while(e->next  != NULL){ //compare end of horizontal list (edge)
			printf(" --> [");
			printf(" %s ",e->next->connectsTo->element);	
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