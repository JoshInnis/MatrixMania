#ifndef MATRIX_H
#define MATRIX_H

struct Matrix {
        int rows;
        int columns;
        int **data;
} Matrix;

struct Matrix *makeMatrix(int rows, int columns);
struct Matrix *multiplyMatrix(struct Matrix *A, struct Matrix *B);
void printMatrix(struct Matrix *m);
struct Matrix *makeIdentityMatrix(int size);
struct Matrix *loadMatrix(char *file);
struct Matrix *makeTransposeMatrix(struct Matrix *A);
struct Matrix *copyMatrix(struct Matrix *A);
struct Matrix *swapMatrixRows(struct Matrix *A, int row_1, int row_2);
struct Matrix *multiplyMatrixRowByScalar(struct Matrix *A, int row, int scalar);
struct Matrix *typeThreeElementaryRowOperation(struct Matrix *matrix, int r, int s, int scalar);



#endif
