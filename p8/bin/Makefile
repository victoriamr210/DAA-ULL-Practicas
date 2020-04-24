IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src

LIBS=-lm

_OBJ = main.o graph.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/graph.hpp $(IDIR)/strategy.hpp $(IDIR)/voraz.hpp $(IDIR)/solution.hpp $(IDIR)/grasp.hpp $(IDIR)/newVoraz.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/graph.o: $(ODIR)/graph.cpp $(IDIR)/graph.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

# $(ODIR)/voraz.o: $(ODIR)/voraz.cpp $(IDIR)/voraz.hpp 
# 	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~

