CC = g++
FLAGS = -lm

.PHONY: clean all

all:  projetoRSAencriptacao projetoRSAdesencriptacao

clean:
	-del *.o projetoRSAdesencriptacao projetoRSAencriptacao

projetoRSAencriptacao:projetoRSAencriptacao.cpp cifraRSA.o
	${CC} -o $@ $@.cpp cifraRSA.o

projetoRSAdesencriptacao: projetoRSAdesencriptacao.cpp cifraRSA.o
	${CC} -o $@ $@.cpp cifraRSA.o
