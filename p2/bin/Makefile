IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src

LIBS=-lm

_OBJ = main.o cinta.o memoria.o programa.o instruccion.o simulador.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main


$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/cinta.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/cinta.o: $(ODIR)/cinta.cpp $(IDIR)/cinta.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/memoria.o: $(ODIR)/memoria.cpp $(IDIR)/memoria.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/programa.o: $(ODIR)/programa.cpp $(IDIR)/programa.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/instruccion.o: $(ODIR)/instruccion.cpp $(IDIR)/instruccion.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/simulador.o: $(ODIR)/simulador.cpp $(IDIR)/simulador.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
