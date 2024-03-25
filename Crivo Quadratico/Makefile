CC = g++
FLAGS = -lm

.PHONY: clean all

all: crivoquadratico

clean:
	-del *.o crivoquadratico
	
crivoquadratico: crivoquadratico.cpp cq.o
	${CC} -o $@ $@.cpp cq.o

