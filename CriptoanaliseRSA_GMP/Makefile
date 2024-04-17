CC = g++
FLAGS = -lm
GMP =  -lgmpxx -lgmp

.PHONY: clean all

all: metodoDivisao metodoEuclides metodoFermat compara geraPrimos\
	testaMetodoDivisao testaMetodoEuclides testaMetodoFermat
clean:
	-rm *.o metodoDivisao metodoEuclides metodoFermat 

metodoDivisao: metodoDivisao.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

metodoEuclides: metodoEuclides.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

metodoFermat: metodoFermat.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

criptoanalise: criptoanalise.cpp
	${CC}  -c $@.cpp ${GMP}

compara: compara.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

geraPrimos: geraPrimos.cpp 
	${CC} -o $@ $@.cpp ${GMP}

testaMetodoDivisao: testaMetodoDivisao.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

testaMetodoEuclides: testaMetodoEuclides.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

testeMetodoFermat: testeMetodoFermat.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}
