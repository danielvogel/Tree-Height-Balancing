/*Include a list of dependency graphs*/

#ifndef DEPENDENCYGRAPHS_H_
#define DEPENDENCYGRAPHS_H_

/*includes*/
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

static int numberOfGraphs = 0;

/*dependency struct*/
typedef struct dependencyGraph{
	graph *g;
	struct dependenyGraph *next;
} depGraph;

extern depGraph* dg;		//global variable for dependency graphs

typedef struct fileNames{
	char* file;
	FILE* f;
	int isValid;
	struct fileNames * next;
}fName;

#define VALID			1		// thats called if the parsed syntax was correct
#define NOT_VALID		0		// thats called if the parsed syntax was not correct
#define FOUND_NO_GRAPHS	2		// no graphs found

#define VERTEX_DEFINE	"vertex:"
#define VERTEX_DELIMITER_OPEN	'['
#define VERTEX_DELIMITER_CLOSE	']'

#define EDGE_DEFINE	'edge:'
#define EDGE_DELIMITER	','
#define EDGE_CONNECTION	'->'


/*function prototypes*/

/**
 *	@brief parse input to dependency graph
 *	@param char* is the directory that will scan  dependency graphs
 *	@return VALIDE if the parsed syntax was correct
 *	@return NOT_VALIDE	if the parsed syntax was not correct 
 *	@return FOUND_NO_GRAPHS
 */
depGraph* parseToDependencyGraph(char*);

/**
  *	@brief concat file and path of the directory
  *	@param	directory is the directory path
  *	@param	fileName is the name of the graph file
  *	@return get the full filepath
  */
char* filePath(char*, char* );

/*
create dependency graph
*/
void createDependencyGraph(depGraph*);

void getNameofFiles(char* ,fName*);
#endif /* DEPENDENCYGRAPHS_H_ */
