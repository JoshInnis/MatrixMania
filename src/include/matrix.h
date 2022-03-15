#ifndef MATRIX_H
#define MATRIX_H

typedef struct Matrix {
        int rows;
        int columns;
        int **data;
} Matrix;

Matrix *makeMatrix(int rows, int columns);
Matrix *multiplyMatrix(Matrix *A, Matrix *B);
void printMatrix(Matrix *m);
Matrix *makeIdentityMatrix(int size);
Matrix *loadMatrix(char *file);
Matrix *makeTransposeMatrix(Matrix *A);
Matrix *copyMatrix(Matrix *A);
Matrix *swapMatrixRows(Matrix *A, int row_1, int row_2);
Matrix *multiplyMatrixRowByScalar(Matrix *A, int row, int scalar);
Matrix *typeThreeElementaryRowOperation(Matrix *matrix, int r, int s, int scalar);
int isRowEchelonForm(Matrix *matrix);


#endif
