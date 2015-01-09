#include "dependency_graph.h"

void getNameofFiles(char* directory, fName* fn){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (directory)) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	    printf ("%s\n", ent->d_name);
	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
	  perror ("");
}
}

int parseToDependencyGraph(char* directory)
{
  FILE *file;
  char *mode = "r";
  fName *fn = (fName*)malloc(sizeof(fName*));

  //first get all filenames in directory
  getNameofFiles(directory,fn);
/*
  file = fopen("in.list", mode);

  if (ifp == NULL) {
    fprintf(stderr, "Can't open input file in.list!\n");
    exit(1);
  }

  ofp = fopen(outputFilename, "w");

  if (ofp == NULL) {
    fprintf(stderr, "Can't open output file %s!\n", outputFilename);
    exit(1);
  }

  while (fscanf(ifp, "%s %d", username, &score) == 2) {
    fprintf(ofp, "%s %d\n", username, score+10);
  }

  fclose(ifp);
  fclose(ofp);*/
  
}

void createDependencyGraph(depGraph* dg)
{

}