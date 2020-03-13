IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src

LIBS=-lm

_OBJ = main.o monomio.o polinomio.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/monomio.hpp $(IDIR)/polinomio.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/monomio.o: $(ODIR)/monomio.cpp $(IDIR)/monomio.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/polinomio.o: $(ODIR)/polinomio.cpp $(IDIR)/polinomio.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
