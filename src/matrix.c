

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

//#typedef bool int;
#define true 1
#define false 0


void printMatrix(Matrix *m) {

        printf("[\n");

        for (int i = 0; i < m->rows; i ++) {

                printf("[");

                for (int j = 0; j < m->columns; j++) {
                        if (j == m->columns - 1) {
                                printf("%i", m->data[i][j]);
                        } else {
                                printf("%i, ", m->data[i][j]);
                        }

                }

                printf("]\n");
        }

        printf("]\n");
}

Matrix *addMatrix(Matrix *A, Matrix *B) {
	Matrix *C = makeMatrix(A->rows, B->columns);

        for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < B->columns; j++) {
                	C->data[i][j] = A->data[i][j] + B->data[i][j];
                }
        }

        return C;
}

Matrix *subtractMatrix(Matrix *A, Matrix *B) {
        Matrix *C = makeMatrix(A->rows, B->columns);

        for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < B->columns; j++) {
                        C->data[i][j] = A->data[i][j] - B->data[i][j];
                }
        }

        return C;
}

Matrix *multiplyMatrix(Matrix *A, Matrix *B) {
        Matrix *C = makeMatrix(A->rows, B->columns);

        for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < B->columns; j++) {
                        for (int k = 0; k < A->columns; k ++) {
                                C->data[i][j] += A->data[i][k] * B->data[k][j];
                        }

                }

        }

        return C;
}

Matrix *makeMatrix(int rows, int columns) {
        Matrix *A = malloc(sizeof(Matrix));

        A->rows = rows;
        A->columns = columns;

        A->data = malloc(sizeof(int *) * rows);

        for (int i = 0; i < rows; i++) {
                A->data[i] = malloc(sizeof(int) * columns);
        }

        return A;
}

Matrix *makeIdentityMatrix(int size) {
        Matrix *mat = makeMatrix(size, size);
        for (int i = 0; i < size; i++) {
                mat->data[i][i] = 1;
        }

        return mat;
}

Matrix *loadMatrix(char *file) {
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        fp = fopen(file, "r");
        int rows, columns;

        read = getline(&line, &len, fp);
        sscanf(line, "%i %i", &rows, &columns);

        Matrix *mat = makeMatrix(rows, columns);

        int cur_row = 0;
        while ((read = getline(&line, &len, fp)) != -1) {
                int cur_col = 0;

                char *token;
                char delim[2] = " ";
                token = strtok(line, delim);

                while( token != NULL ) {
                        mat->data[cur_row][cur_col] = atoi(token);

                        token = strtok(NULL, delim);

                        cur_col++;
                }
                cur_row++;
        }

        return mat;
}


Matrix *makeTransposeMatrix(Matrix *A) {
        Matrix *B = makeMatrix(A->columns, A->rows);

        for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                        B->data[j][i] = A->data[i][j];
                }
        }

        return B;
}

Matrix *copyMatrix(Matrix *A) {
        Matrix *B = makeMatrix(A->rows, A->columns);

        for (int i = 0; i < B->rows; i++) {
                for(int j = 0; j < B->columns; j++) {
                        B->data[i][j] = A->data[i][j];
                }
        }

        return B;
}

Matrix *swapMatrixRows(Matrix *A, int row_1, int row_2) {
        Matrix *B = copyMatrix(A);
        int *tmp = B->data[row_1];

        B->data[row_1] = B->data[row_2];
        B->data[row_2] = tmp;

        return B;
}

Matrix *multiplyMatrixRowByScalar(Matrix *A, int row, int scalar) {
        Matrix *B = copyMatrix(A);

        for (int i = 0; i < B->columns; i++) {
                B->data[row][i] *= scalar;
        }

        return B;
}


/*
Matrix *vectorToMatrixRow(Matrix *matrix, Vector *vector, int row) {
        Matrix *copy_matrix = copyMatrix(matrix);


        for (int i = 0; i < matrix->columns; i++) {
                copy_matrix->data[row][i] = vector->data[i];
        }

        return copy_matrix;
}

Vector *vectorAdd(Vector *a, Vector *b) {
        Vector *v = copyVector(a);


        for (int i = 0; i < v->size; i++) {
                v->data[i] += b->data[i];
        }

        return v;
}

Matrix *typeThreeElementaryRowOperation(Matrix *matrix, int r, int s, int scalar) {
        return vectorToMatrixRow(
                matrix,
                vectorAdd(
                        scalarMultiplyVector(matrixRowToVector(matrix, s), scalar),
                        matrixRowToVector(matrix, r)
                ),
                r
        );
}
*/


typedef struct LeadingEntry {
        int value;
        int position;
} LeadingEntry;

typedef struct LeadingEntryVector {
        LeadingEntry **data;
} LeadingEntryVector;

LeadingEntry *makeLeadingEntry(int value, int position) {
        LeadingEntry *entry = malloc(sizeof(LeadingEntry *));

        entry->value = value;
        entry->position = position;

        return entry;
}

LeadingEntryVector *makeLeadingEntryVector(int size) {
        LeadingEntryVector *vector = malloc(sizeof(LeadingEntryVector));

        vector->data = malloc(size * sizeof(LeadingEntry *));

        return vector;
}

LeadingEntry *getLeadingEntry(Matrix *matrix, int row) {

        for(int i = 0; i < matrix->columns; i++) {
                if (matrix->data[row][i] != 0)
                        return makeLeadingEntry(matrix->data[row][i], i);
        }

        return makeLeadingEntry(0, -1);
}

LeadingEntryVector *getLeadingEntryVector(Matrix *matrix) {
        LeadingEntryVector *vector = makeLeadingEntryVector(matrix->rows);

        for (int i = 0; i < matrix->rows; i++) {
                vector->data[i] = getLeadingEntry(matrix, i);
        }

        return vector;
}

int isRowEchelonForm(Matrix *matrix) {
        LeadingEntryVector *lev = getLeadingEntryVector(matrix);

        int row = 0;
        while (row < matrix->rows && lev->data[row]->position != -1) {
                if (lev->data[row]->value != 1)
                        return false;

                for (int i = lev->data[row]->position + 1; i < matrix->columns; i++) {
                        if (matrix->data[row][i] != 0)
                                return false;
                }
                row++;
        }

        while (row < matrix->rows) {
                if (lev->data[row]->position != -1)
                        return false;
                row++;
        }

        return true;
}
/*
Matrix *splitSquareMatrix(Matrix *x, Matrix *y) {
	Matrix *A, *B, *C, *D;
	Matrix *return_matrix;

	if (matrix->rows == 1) {
		return_matrix = make_matrix(1, 1);
		return_matrix->data[0][0] = x->data[0][0] * y->data[0][0];
		return matrix;
	}

	return_matrix = make_matrix(x->rows, x->columns);

	A = malloc(sizeof(Matrix));
        A->rows = matrix->rows;
        A->columns = matrix->columns;

        B = malloc(sizeof(Matrix));
        B->rows = matrix->rows;
        B->columns = matrix->columns;

	C = malloc(sizeof(Matrix));
        C->rows = matrix->rows;
        C->columns = matrix->columns;

	D = malloc(sizeof(Matrix));
        D->rows = matrix->rows;
        D->columns = matrix->columns;

	return
}
*/
Matrix *multiplyMatrixStrassen(Matrix *A, Matrix *B) {
	

}
