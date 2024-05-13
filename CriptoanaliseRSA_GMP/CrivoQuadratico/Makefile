CC = g++
FLAGS = -lm
GMP =  -lgmpxx -lgmp -lmpfr

.PHONY: clean all

all: crivoquadratico 

clean:
	-del *.o crivoquadratico 

cq: cq.cpp
	${CC}  -c $@.cpp ${GMP}

crivoquadratico: crivoquadratico.cpp cq
	${CC} -o $@ $@.cpp cq.o ${GMP}


