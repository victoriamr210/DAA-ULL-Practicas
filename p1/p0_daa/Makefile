IDIR =include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=src

LIBS=-lm

_OBJ = main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main


$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/matrix.hpp $(IDIR)/strategy.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
