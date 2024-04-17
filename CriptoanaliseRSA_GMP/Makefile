CC = g++
FLAGS = -lm
GMP =  -lgmpxx -lgmp

.PHONY: clean all

all: metodoDivisao metodoEuclides metodoFermat compara geraPrimos\
	testaMetodoDivisao testaMetodoEuclides testaMetodoFermat

clean:
	-rm *.o metodoDivisao metodoEuclides metodoFermat 

metodoDivisao: metodoDivisao.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

metodoEuclides: metodoEuclides.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

metodoFermat: metodoFermat.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

criptoanalise: criptoanalise.cpp
	${CC}  -c $@.cpp ${GMP}

compara: compara.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

geraPrimos: geraPrimos.cpp 
	${CC} -o $@ $@.cpp ${GMP}

testaMetodoDivisao: testaMetodoDivisao.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

testaMetodoEuclides: testaMetodoEuclides.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

testaMetodoFermat: testaMetodoFermat.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}
