IDIR =src/include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=src
LDIR =../lib

LIBS=-lm

_DEPS = matrix.h vector.h sparseMatrix.h tensor.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = MatrixMadness.o matrix.o vector.o sparseMatrix.o tensor.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

MatrixMaddness: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ MatrixMaddness 
