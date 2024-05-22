CC = g++
FLAGS = -lm
GMP =  -lgmpxx -lgmp -lmpfr

.PHONY: clean all

all: metodoDivisao metodoEuclides metodoFermat compara geraPrimos\
	testaMetodoDivisao testaMetodoEuclides testaMetodoFermat \
	testaMetodoCrivoQuadratico testaMetodoCrivoQuadraticoV1

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

testaMetodoCrivoQuadratico: testaMetodoCrivoQuadratico.cpp cq
	${CC} -o $@ $@.cpp cq.o ${GMP}

cq: cq.cpp
	${CC}  -c $@.cpp ${GMP}

testaMetodoCrivoQuadraticoV1: testaMetodoCrivoQuadraticoV1.cpp crivoQuadratico
	${CC} -o $@ $@.cpp crivoQuadratico.o ${GMP}

crivoQuadratico: crivoQuadratico.cpp
	${CC}  -c $@.cpp ${GMP}
