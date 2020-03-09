IDIR =../include
CC=g++
CFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src

LIBS=-lm

_OBJ = main.o mergesortS.o mergesortP.o quicksortP.o quicksortS.o framework.o problem.o solution.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: main


$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/mergesortS.hpp $(IDIR)/mergesortP.hpp $(IDIR)/framework.hpp $(IDIR)/quicksortP.hpp $(IDIR)/quicksortS.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/mergesortP.o: $(ODIR)/mergesortP.cpp $(IDIR)/mergesortP.hpp $(IDIR)/problem.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/mergesortS.o: $(ODIR)/mergesortS.cpp $(IDIR)/mergesortS.hpp $(IDIR)/solution.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/quicksortP.o: $(ODIR)/quicksortP.cpp $(IDIR)/quicksortP.hpp $(IDIR)/problem.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/quicksortS.o: $(ODIR)/quicksortS.cpp $(IDIR)/quicksortS.hpp $(IDIR)/solution.hpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/framework.o: $(ODIR)/framework.cpp $(IDIR)/framework.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/problem.o: $(ODIR)/problem.cpp $(IDIR)/problem.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/solution.o: $(ODIR)/solution.cpp $(IDIR)/solution.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(INCDIR)/*~
