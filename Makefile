#
# Makefile for compilerbau
#

#CFLAGS=
#LDFLAGS=

.PHONY: all clean

all : MQTTv3

MQTTv3 : main.o 
	${CXX} $^ -o $@ ${LDFLAGS}


main.o : main.cpp
	${CXX} -c $^ -o $@ ${CFLAGS}



clean : 
	#-rm -f *.o m MQTTv3
