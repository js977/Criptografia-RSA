CC = g++
FLAGS = -lm

.PHONY: clean all

all: mdivisao metodoeuclides metodofermat

clean:
	-del *.o mdivisao metodoeuclides metodofermat
	
mdivisao: mdivisao.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o

metodoeuclides: metodoeuclides.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o

metodofermat: metodofermat.cpp criptoanalise.o
	${CC} -o $@ $@.cpp criptoanalise.o
