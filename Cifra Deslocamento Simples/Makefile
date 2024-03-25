CC = g++
FLAGS = -lm

.PHONY: clean all

all: projetodsencriptacao projetodsdesencriptacao projetodsquebracifra

clean:
	-del *.o projetodsencriptacao projetodsdesencriptacao projetodsquebracifra
	
projetodsencriptacao: projetodsencriptacao.cpp cifrads.o
	${CC} -o $@ $@.cpp cifrads.o

projetodsdesencriptacao: projetodsdesencriptacao.cpp cifrads.o
	${CC} -o $@ $@.cpp cifrads.o

projetodsquebracifra: projetodsquebracifra.cpp cifrads.o
	${CC} -o $@ $@.cpp cifrads.o
