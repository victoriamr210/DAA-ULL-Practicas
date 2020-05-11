IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src

LIBS=-lm

_OBJ = main.o problem.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main

$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/problem.hpp $(IDIR)/voraz.hpp $(IDIR)/solution.hpp $(IDIR)/newVoraz.hpp $(IDIR)/GRASP.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/problem.o: $(ODIR)/problem.cpp $(IDIR)/problem.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

# $(ODIR)/voraz.o: $(ODIR)/voraz.cpp $(IDIR)/voraz.hpp 
# 	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~

