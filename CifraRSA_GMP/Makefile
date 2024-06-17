CC = g++
FLAGS = -lm
GMP =  -lgmpxx -lgmp
.PHONY: clean all

all:  projetoRSAencriptacao projetoRSAdesencriptacao

clean:
	-del *.o projetoRSAdesencriptacao projetoRSAencriptacao

projetoRSAencriptacao:projetoRSAencriptacao.cpp cifraRSA.o
	${CC} -o $@ $@.cpp cifraRSA.o ${GMP}
projetoRSAdesencriptacao: projetoRSAdesencriptacao.cpp cifraRSA.o
	${CC} -o $@ $@.cpp cifraRSA.o
