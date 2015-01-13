#include "dependency_graph.h"

depGraph* dg;

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
	
	//printf("Size of directory %s : %d\nSize of fileName %s : %d\n",directory, sDirectory,fileName, sfileName);
	sprintf(filepath,"%s%s",directory,fileName);	//print string formatted 

	return filepath;
}

FILE* openNewFile(char* path, char* mode){
	FILE *file = fopen(path, mode);
 	
	return file;
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


int parseEdge()
{

}

int parseVertex(FILE* file)
{
	char character;
	char strVertex[255];
	int i = 0;

	while( ( character = fgetc(file) ) != VERTEX_DELIMITER_CLOSE ){
		strVertex[i++] = character;
	}
		strVertex[i] =  '\0';
		// printf("%c",character);		// if use %s formatter you get segmentation fault !!!

	//GraphAddVertex(dg->g, strVertex, NULL);	
	
}

int parseFile(fName* fn)
{
	
  	size_t *t = malloc(0);
  	int nRet;
   	char **gptr = malloc(sizeof(char*));
    *gptr = NULL;
    char ch;


    while( ( ch = fgetc(fn->f) ) != EOF ){
    	//printf("Line: ");
    	do{
    		if(ch == VERTEX_DELIMITER_OPEN)
    			parseVertex(fn->f);

    		// printf("%c",ch);
    	}while((ch = fgetc(fn->f)) != '\n');
    	
  	}
/*
    //read line from file. getline realloc memory for gptr
    while( (nRet=getline(gptr, t, fn->f)) > 0){    
    //	printf("Line %d: %s",nRet,*gptr);
    	//walk step by step through line
	 printf("Step: %s\n",*gptr);
		//check if vertex defined 
		//parse the vertexs
		//save the vertex onto graph struct
	
    }*/
	
	 		 
}
 
depGraph* parseToDependencyGraph(char* directory)
{
  FILE *file;
  DIR *dir;
  char* filepath;
  struct dirent *ent;
  fName *fn = (fName*)malloc(sizeof(fName)); //alocate first list element (head)
  depGraph* head;
  dg = (depGraph*)malloc(sizeof(depGraph));
  head = dg;

printf("FRONT: %p\n", head);
  //first get all filenames in directory
  	if ((dir = opendir (directory)) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	    if(strstr(ent->d_name,".depg") != NULL){ 	 //if the file is a dependency graph type
	    	dg->g = GraphCreate();		//new file => new Graph
	    	dg->next = (depGraph*)malloc(sizeof(depGraph));

	    	filepath = filePath(directory,ent->d_name);
	    	printf("Found file %s %d\n",ent->d_name,ent->d_type);
	    	printf("Size of file %d bytes\n",fsize(filepath));

	    	//set the next file struct
			fn->file = filepath;
			fn->next = (fName*)malloc(sizeof(fName));
			fn->isValid = 0;

	    	fn->f = fopen(fn->file, "r");
	    	if (file == NULL){
	    	    fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
	            return 1;
        	}
			parseFile(fn);	//parse file and  create dependency graph 	
			printGraph(dg->g);
     		fn = fn->next; 
     		dg = dg->next;
	    }
	  }
	  closedir (dir);		//close the opened directory
	} else {
	  /* could not open directory */
	  perror ("Error - ");
 }
printf("END: %p\n", head);

 return head;	//liefert den etzten graphen
}
