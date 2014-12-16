#
# Makefile for compilerbau
#

#CFLAGS=
#LDFLAGS=

.PHONY: all clean

all : DEMO

DEMO : main.o 
	${CXX} $^ -o $@ ${LDFLAGS}


main.o : main.c
	${CXX} -c $^ -o $@ ${CFLAGS}



clean : 
	-rm -f *.o m DEMO
