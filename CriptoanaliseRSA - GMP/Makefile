CC = g++
FLAGS = -lm
GMP =  -lgmpxx -lgmp

.PHONY: clean all

all: metodoDivisao metodoEuclides metodoFermat compara

clean:
	-del *.o metodoDivisao metodoEuclides metodoFermat 

metodoDivisao: metodoDivisao.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

metodoEuclides: metodoEuclides.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

metodoFermat: metodoFermat.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

criptoanalise: criptoanalise.cpp
	${CC}  -c $@.cpp ${GMP}

compara: compara.cpp  metodoDivisao metodoEuclides metodoFermat
	${CC}  -o  $@  $@.cpp ${GMP}
