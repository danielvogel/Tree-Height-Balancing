/*Include a list of dependency graphs*/

#ifndef DEPENDENCYGRAPHS_H_
#define DEPENDENCYGRAPHS_H_

/*includes*/
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <malloc.h>

static int numberOfGraphs = 0;

/*dependency struct*/
typedef struct dependencyGraph{
	struct dependenyGraph *next;
} depGraph;

typedef struct fileNames{
	char* file;
	struct fileNames * next;
}fName;

#define VALIDE		1		// thats called if the parsed syntax was correct
#define NOT_VALIDE	0		// thats called if the parsed syntax was not correct

/*function prototypes*/

/**
 *	@brief parse input to dependency graph
 *	@param char* is the directory that will scan  dependency graphs
 *	@return VALIDE if the parsed syntax was correct
 *	@return NOT_VALIDE	if the parsed syntax was not correct 
 */
int parseToDependencyGraph(char*);

/*
create dependency graph
*/
void createDependencyGraph(depGraph*);

void getNameofFiles(char* ,fName*);
#endif /* DEPENDENCYGRAPHS_H_ */
