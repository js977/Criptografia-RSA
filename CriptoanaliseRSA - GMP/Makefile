CC = g++
FLAGS = -lm
GMP =  -lgmpxx -lgmp

.PHONY: clean all

all: mdivisao metodoeuclides metodofermat 

clean:
	-del *.o mdivisao metodoeuclides metodofermat 

	
mdivisao: mdivisao.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

metodoeuclides: metodoeuclides.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

metodofermat: metodofermat.cpp criptoanalise
	${CC} -o $@ $@.cpp criptoanalise.o ${GMP}

criptoanalise: criptoanalise.cpp
	${CC}  -c $@.cpp ${GMP}
