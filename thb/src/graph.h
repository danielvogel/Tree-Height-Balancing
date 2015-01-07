
/**
	A graph is yet another data structure that you can use to store information. 
	Unlike trees, which have a strict hierarchical structure, graphs are more flexible. 
	As mentioned, graphs are pretty generic data structures in that they can be used to represent lots of things. 
	Thus, exactly what operations we'll want for a graph will depend on what we want to do with it.
*/


typedef struct vertexTag {
  char* element;
  int isVisited;
  typedef struct edgeTag {
  		struct vertexTag *connectsTo;
  		struct edgeTag *next;
   } *edge;
  struct vertexTag *next;
} vertex;


typedef struct graphTag{
	vertex *vertices;
}graph;


/*functions protoype*/

void GraphAddVertex();
void GraphAddEdge();
void GraphCreate();
void GrapsDestroy();