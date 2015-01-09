#
# Makefile for compilerbau
#

#CFLAGS=
#LDFLAGS=
CC=gcc
CFLAGS=-c -ggdb -I/usr/local/include 
SOURCES= src/main.c src/thb.c src/codetree.c src/namequeue.c src/graph.c src/dependency_graph.c
DISTDIR= bin/
ODIR= obj
SDIR= src
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=thb

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(ODIR)
	mkdir -p $(DISTDIR)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(DISTDIR)$@
	
	mv $(SDIR)/*.o obj
.c.o:   
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(ODIR)/*o bin/$(EXECUTABLE)
