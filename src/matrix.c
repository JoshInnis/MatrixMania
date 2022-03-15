

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

//#typedef bool int;
#define true 1
#define false 0


void printMatrix(struct Matrix *m) {

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

struct Matrix *multiplyMatrix(struct Matrix *A, struct Matrix *B) {
        struct Matrix *C = makeMatrix(A->rows, B->columns);

        for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < B->columns; j++) {
                        for (int k = 0; k < A->columns; k ++) {
                                C->data[i][j] += A->data[i][k] * B->data[k][j];
                        }

                }

        }

        return C;
}

struct Matrix *makeMatrix(int rows, int columns) {
        struct Matrix *A = malloc(sizeof(Matrix));

        A->rows = rows;
        A->columns = columns;

        A->data = malloc(sizeof(int *) * rows);

        for (int i = 0; i < rows; i++) {
                A->data[i] = malloc(sizeof(int) * columns);
        }

        return A;
}

struct Matrix *makeIdentityMatrix(int size) {
        struct Matrix *mat = makeMatrix(size, size);
        for (int i = 0; i < size; i++) {
                mat->data[i][i] = 1;
        }

        return mat;
}

struct Matrix *loadMatrix(char *file) {
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        fp = fopen(file, "r");
        int rows, columns;

        read = getline(&line, &len, fp);
        sscanf(line, "%i %i", &rows, &columns);

        struct Matrix *mat = makeMatrix(rows, columns);

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


struct Matrix *makeTransposeMatrix(struct Matrix *A) {
        struct Matrix *B = makeMatrix(A->columns, A->rows);

        for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                        B->data[j][i] = A->data[i][j];
                }
        }

        return B;
}

struct Matrix *copyMatrix(struct Matrix *A) {
        struct Matrix *B = makeMatrix(A->rows, A->columns);

        for (int i = 0; i < B->rows; i++) {
                for(int j = 0; j < B->columns; j++) {
                        B->data[i][j] = A->data[i][j];
                }
        }

        return B;
}

struct Matrix *swapMatrixRows(struct Matrix *A, int row_1, int row_2) {
        struct Matrix *B = copyMatrix(A);
        int *tmp = B->data[row_1];

        B->data[row_1] = B->data[row_2];
        B->data[row_2] = tmp;

        return B;
}

struct Matrix *multiplyMatrixRowByScalar(struct Matrix *A, int row, int scalar) {
        struct Matrix *B = copyMatrix(A);

        for (int i = 0; i < B->columns; i++) {
                B->data[row][i] *= scalar;
        }

        return B;
}


/*
struct Matrix *vectorToMatrixRow(struct Matrix *matrix, struct Vector *vector, int row) {
        struct Matrix *copy_matrix = copyMatrix(matrix);


        for (int i = 0; i < matrix->columns; i++) {
                copy_matrix->data[row][i] = vector->data[i];
        }

        return copy_matrix;
}

struct Vector *vectorAdd(struct Vector *a, struct Vector *b) {
        struct Vector *v = copyVector(a);


        for (int i = 0; i < v->size; i++) {
                v->data[i] += b->data[i];
        }

        return v;
}

struct Matrix *typeThreeElementaryRowOperation(struct Matrix *matrix, int r, int s, int scalar) {
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


struct LeadingEntry {
        int value;
        int position;
} LeadingEntry;

struct LeadingEntryVector {
        struct LeadingEntry **data;
} LeadingEntryVector;

struct LeadingEntry *makeLeadingEntry(int value, int position) {
        struct LeadingEntry *entry = malloc(sizeof(struct LeadingEntry *));

        entry->value = value;
        entry->position = position;

        return entry;
}

struct LeadingEntryVector *makeLeadingEntryVector(int size) {
        struct LeadingEntryVector *vector = malloc(sizeof(LeadingEntryVector));

        vector->data = malloc(size * sizeof(struct LeadingEntry *));

        return vector;
}

struct LeadingEntry *getLeadingEntry(struct Matrix *matrix, int row) {

        for(int i = 0; i < matrix->columns; i++) {
                if (matrix->data[row][i] != 0)
                        return makeLeadingEntry(matrix->data[row][i], i);
        }

        return makeLeadingEntry(0, -1);
}

struct LeadingEntryVector *getLeadingEntryVector(struct Matrix *matrix) {
        struct LeadingEntryVector *vector = makeLeadingEntryVector(matrix->rows);

        for (int i = 0; i < matrix->rows; i++) {
                vector->data[i] = getLeadingEntry(matrix, i);
        }

        return vector;
}

int isRowEchelonForm(struct Matrix *matrix) {
        struct LeadingEntryVector *lev = getLeadingEntryVector(matrix);

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
