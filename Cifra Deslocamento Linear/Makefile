CC = g++
FLAGS = -lm

.PHONY: clean all

all: projetodlencriptacao projetodldesencriptacao projetodlquebracifra

clean:
	-del *.o projetodlencriptacao projetodldesencriptacao projetodlquebracifra

projetodldesencriptacao: projetodldesencriptacao.cpp cifradl.o
	${CC} -o $@ $@.cpp cifradl.o
	
projetodlquebracifra: projetodlquebracifra.cpp cifradl.o
	${CC} -o $@ $@.cpp cifradl.o
projetodlencriptacao: projetodlencriptacao.cpp cifradl.o
	${CC} -o $@ $@.cpp cifradl.o
