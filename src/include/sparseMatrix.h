#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include "matrix.h"

typedef struct SparseMatrix {
	int size;
	int rowCount;
	int colCount;
        int *rows;
        int *columns;
        int *values;
} SparseMatrix;

SparseMatrix *makeSparseMatrix(int rows, int columns, int size);
void printSparseMatrix(SparseMatrix *m);
SparseMatrix *matrixToSparseMatrix(Matrix *matrix);
//SparseMatrix *loadSparseMatrix(char *file);
//SparseMatrix *copySparseMatrix(Matrix *A);

#endif
