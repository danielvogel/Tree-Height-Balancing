#include "dependency_graph.h"

int numberOfGraphs = 0;

void append(char* s, char c)
{
        int len = strlen(s);
        s[len] = c;
        s[len+1] = '\0';
}

off_t fsize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

	fprintf(stderr, "Cannot determine size of %s: %s\n",
            filename, strerror(errno));

    return -1; 
}

char* filePath(char* directory, char* fileName){
	int sDirectory = strlen(directory) ;
	int sfileName = strlen(fileName) ; 
	char* filepath = (char*)malloc(sizeof(char) + sDirectory + sfileName + 1); // allocate memory for filepath (+1 because the \0 at the end)

	sprintf(filepath,"%s%s",directory,fileName);	//print string formatted 

	return filepath;
}

FILE* openNewFile(char* path, char* mode){
	return fopen(path, mode);
}


void getNameofFiles(char* directory, fName* fn){
	DIR *dir;
	struct dirent *ent;
	
	if ((dir = opendir (directory)) != NULL) {

	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	   
	    if(strstr(ent->d_name,"depg") != NULL){ 	 
 		    fn->file = filePath(directory,ent->d_name);	//write full filepath to fn
 		   // f[numberOfGraphs] = fopen(fn->file, "r");
		   	printf("Filename: %s\n",fn->file);
	   		fn->next = (fName*)malloc(sizeof(fName*));
	   	 	fn = fn->next;
	   		numberOfGraphs++;	// counts founded graphs
	    }
	  }
	  printf("Found %d graphs\n", numberOfGraphs);
	  closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("Error - ");
 }
}

char* getVertex1ByDelimiter(char* sEdge)
{
	char* vertex1, *begin;
	int i=0;
	if((begin = strchr(sEdge,VERTEX_DELIMITER_OPEN))){
		vertex1 = malloc(strlen(begin));	
		i=1;	//first character is the open delimiter
		while(begin[i] != '-')
			append(vertex1,begin[i++]);	

		return vertex1;	
	}else
	return NULL;
}

char* getVertex2ByDelimiter(char* sEdge)
{
	char* vertex2, *begin;
	int i=0;
	if((begin = strchr(sEdge,'>'))){
		vertex2 = malloc(strlen(begin));	
		i=1;	//first character is the open delimiter
		while(begin[i] != VERTEX_DELIMITER_CLOSE)
			append(vertex2,begin[i++]);	

		return vertex2;	
	}else
	return NULL;
}

char* getVertexType(char* sVertex)
{
	int i = 0;
	char *begin, *sType;

	if((begin = strchr(sVertex,VERTEX_TYPE_OPEN))){
		sType = malloc(strlen(begin));	
		i=1;	//first character is the open delimiter

		while(begin[i] != VERTEX_TYPE_CLOSE)
			append(sType,begin[i++]);		
		
		return sType;
	}else
	return NULL;
}

char* getVertexNameByName(char* vertexName)
{
	int i = 0;
	char *begin, *sType;

	if((begin = strchr(vertexName,VERTEX_DELIMITER_OPEN))){
		sType = malloc(strlen(begin));	
		i=1;	//first character is the open delimiter

		while(begin[i] != VERTEX_DELIMITER_CLOSE)
			append(sType,begin[i++]);		
		
		return sType;

	}else
	return NULL;
}

char* getVertexName(char* sVertex)
{
	int i = 0;
	char *begin, *sType;

	if((begin = strchr(sVertex,VERTEX_DELIMITER_OPEN))){
		sType = malloc(strlen(begin));	
		i=1;	//first character is the open delimiter

		while(begin[i] != VERTEX_TYPE_OPEN)
			append(sType,begin[i++]);		
		
		return sType;

	}else
	return NULL;
}

void push(UEVarQueue * head, char* val) {
    UEVarQueue * current = head;

        while (current->next != NULL) {
            current = current->next;
        }
        /* now we can add a new variable */
        current->next = (UEVarQueue*) malloc(sizeof(UEVarQueue));
        current->name = val;
}

void parseUEVar(depGraph *dg, char* UEVar)
{
	char *sptr ,*vertexElement;
	//UEVarQueue *current = dg->uevar;

	sptr = strtok(UEVar, ":");	// remove vertex string
	sptr = strtok(NULL, EDGE_DELIMITER);
	while(sptr != NULL) {

		vertexElement = getVertexNameByName(sptr);
		 push(dg->uevar,vertexElement);
		
	 	sptr = strtok(NULL, EDGE_DELIMITER);
	}
}

void parseEdge(graph *depGraph, char* sEdge)
{
	char *sptr;
	char *vertex1, *vertex2;
	vertex *v1, *v2;

	// initialisieren und ersten Abschnitt erstellen
	sptr = strtok(sEdge, ":");	// remove vertex string
	sptr = strtok(NULL, EDGE_DELIMITER);
	while(sptr != NULL) {
		//printf("Abschnitt gefunden: %s\n", sptr);
		vertex1 = getVertex1ByDelimiter(sptr);
		vertex2 = getVertex2ByDelimiter(sptr);

		v1 = GraphGetVertexByName(depGraph,vertex1);
		v2 = GraphGetVertexByName(depGraph,vertex2);

   		GraphAddEdge(depGraph,v1,v2);

	 	sptr = strtok(NULL, EDGE_DELIMITER);
	}
}

void parseVertex(graph *depGraph, char* sVertex)
{
    char *sptr, *vertexElement, *vertexType;
	int isConst = 0;

	// initialisieren und ersten Abschnitt erstellen
	sptr = strtok(sVertex, ":");	// remove vertex string
	sptr = strtok(NULL, EDGE_DELIMITER);

	while(sptr != NULL) {
		// create next part
		vertexElement = getVertexName(sptr);
		vertexType = getVertexType(sptr);

		if(strcmp(vertexType,VERTEX_CONST)==0)
			isConst = 1;

		if(strcmp(vertexType,VERTEX_VAR)==0)
			isConst = 0;	//isConst = 0, that is a variable not a constant

	 	GraphAddVertex(depGraph,vertexElement,vertexType,isConst, NULL);
	 	
	 	sptr = strtok(NULL, EDGE_DELIMITER);
	}
}

void parseFile(depGraph *dglist, graph *dg, fName* fn)
{
	
  	size_t *t = malloc(0);
  	int nRet;
   	char **gptr = malloc(sizeof(char*));
    *gptr = NULL;

    //read line from file. getline realloc memory for gptr
    while( (nRet=getline(gptr, t, fn->f)) > 0){    
    	//is vertex part of line? Parse vertex
    	if(strstr(*gptr,VERTEX_DEFINE))
    		parseVertex(dg,*gptr);
    	
    	//is edge part of line? Parse edge
    	if(strstr(*gptr,EDGE_DEFINE))
    		parseEdge(dg,*gptr);

    	//is uevar part of line? Parse uevar
    	if(strstr(*gptr,UEVAR_DEFINE))
    		parseUEVar(dglist, *gptr);
    } 		 
}
 
depGraph* parseToDependencyGraph(char* directory)
{
  DIR *dir;
  depGraph* dg;
  char* filepath;
  struct dirent *ent;
  fName *fn = (fName*)malloc(sizeof(fName)); //alocate first list element (head)
  depGraph* head;
  
  dg = (depGraph*)malloc(sizeof(depGraph));
  head = dg;

  printf("Reading graphs from /graphs directory. It is read only files with the extension .depg \n");
  //first get all filenames in directory
  	if ((dir = opendir (directory)) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	    if(strstr(ent->d_name,".depg") != NULL){ 	 //if the file is a dependency graph type
	    	dg->g = GraphCreate();		//new file => new Graph
	    	dg->next = (depGraph*)malloc(sizeof(depGraph));
		dg->uevar = (UEVarQueue*) malloc(sizeof(struct UEVar_queue));
		dg->uevar->next = NULL;
	    	filepath = filePath(directory,ent->d_name);
	    	printf("Found file: %s\n",ent->d_name);
	    	printf("Size of file: %lld bytes\n",(long long int)fsize(filepath));

	    	//set the next file struct
			fn->file = filepath;
			fn->next = (fName*)malloc(sizeof(fName));
			fn->isValid = 0;

	    	fn->f = fopen(fn->file, "r");
	    	if (fn->f == NULL){
	    	    fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
	            return NULL;
        	}
			parseFile(dg,dg->g,fn);	//parse file and  create dependency graph 	
     		fn = fn->next; 
     		
     		//printf("UEVAR: %s\n",dg->uevar->name);
     		dg = dg->next;
     		numberOfGraphs++;	//increment reading graph counter
	    }
	  }
	  closedir (dir);		//close the opened directory
	  printf("Number of graphs: %d\n\n", numberOfGraphs);
	} else {
	  /* could not open directory */
	  perror ("Error - ");
 }

 return head;	//liefert den letzten graphen
}

void printAllGraphs(depGraph* dg){
	while(dg->g != NULL){
		printGraph(dg->g);
		dg = dg->next;
	}
}
