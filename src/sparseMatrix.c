#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sparseMatrix.h"

SparseMatrix *makeSparseMatrix(int rows, int columns, int size) {
	SparseMatrix *sparseMatrix = malloc(sizeof(SparseMatrix));

	sparseMatrix->size = size;
	sparseMatrix->rowCount = rows;
	sparseMatrix->colCount = columns;
	sparseMatrix->rows = malloc(sizeof(int) * size);
	sparseMatrix->columns = malloc(sizeof(int) * size);
	sparseMatrix->values = malloc(sizeof(int) * size);
}

void printSparseMatrix(SparseMatrix *sparseMatrix) {

	printf("row: ");
	for (int i = 0; i < sparseMatrix->size; i++) {
		printf("%i ", sparseMatrix->rows[i]);
	}
	printf("\n");

        printf("col: ");
        for (int i = 0; i < sparseMatrix->size; i++) {
                printf("%i ", sparseMatrix->columns[i]);
        }
        printf("\n");

        printf("val: ");
        for (int i = 0; i < sparseMatrix->size; i++) {
                printf("%i ", sparseMatrix->values[i]);
        }
        printf("\n");
}

SparseMatrix *matrixToSparseMatrix(Matrix *matrix) {
	SparseMatrix *sp;
	int size = 0, cnt = 0;
        int row = 0;
        int col = 0;

	for (int i = 0; i < matrix->rows; i++){
		for (int j = 0; j < matrix->columns; j++) {
			if (matrix->data[i][j] != 0)
				size++;
		}
	}

	sp = makeSparseMatrix(matrix->rows, matrix->columns, size);

	while (cnt < size) {

		if (row == matrix->rows)
			break;

		if (col == matrix->columns) {
			col = 0;
			row++;
		}


		if (matrix->data[row][col] != 0) {
			sp->rows[cnt] = row;
			sp->columns[cnt] = col;
			sp->values[cnt] = matrix->data[row][col];

			cnt++;
		}

		col++;
	}

	return sp;
}
/*
SparseMatrix *loadSparseMatrix(char *file);
SparseMatrix *copySparseMatrix(Matrix *A);
*/

