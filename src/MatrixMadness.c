
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"
#include "vector.h"

//#typedef bool int;
#define true 1
#define false 0

struct Matrix *vectorToMatrixRow(struct Matrix *matrix, struct Vector *vector, int row) {
        struct Matrix *copy_matrix = copyMatrix(matrix);


        for (int i = 0; i < matrix->columns; i++) {
                copy_matrix->data[row][i] = vector->data[i];
        }

        return copy_matrix;
}

struct Vector *matrixColumnToVector(struct Matrix *matrix, int column) {
	struct Vector *vector = makeVector(matrix->rows);

	for (int i = 0; matrix->rows; i++) {
		vector->data[i] = matrix->data[i][column];
	}

	return vector;
}

struct Vector *matrixRowToVector(struct Matrix *matrix, int row) {
	struct Vector *vector = makeVector(matrix->columns);

        for (int i = 0; i < matrix->columns; i++) {
		 vector->data[i] = matrix->data[row][i];
        }

        return vector;
}


struct Vector *scalarMultiplyVector(struct Vector*vector, int scalar) {
	struct Vector *copy_vector = copyVector(vector);

	for (int i = 0; i < copy_vector->size; i++) {
		copy_vector->data[i] *= scalar;
	}

	return copy_vector;
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


int main(const int argc, const char *argv[]) {
	//Vector
/*	struct Vector *v = loadVector("./A.vect");

	printVector(v);
*/
        //Matrix
	struct Matrix *A, *B, *C, *D;

	A = loadMatrix("./a.mat");
        B = loadMatrix("./b.mat");
	C = loadMatrix("./c.mat");
        D = loadMatrix("./d.mat");

	printf("A = ");
	printMatrix(A);

/*
	printf("B = ");
	printMatrix(B);

	printf("A*B = ");
	printMatrix(multiplyMatrix(A, B));

	printf("C = ");
	printMatrix(C);

        printf("D = ");
        printMatrix(D);

	printf("SwapRows(D, 1, 3) = ");
	printMatrix(swapMatrixRows(D, 0, 2));


	printf("multiplyMatrixRowByScalar(A, 0, 5) = ");
	printMatrix(multiplyMatrixRowByScalar(A, 0, 5));
*/


	printf("typeThreeElementaryRowOperation(A, 0, 1, 2) = ");
	printMatrix(typeThreeElementaryRowOperation(A, 0, 1, 2));
/*
        printf("C*D = ");
        printMatrix(multiplyMatrix(C, D));

        printf("D*C = ");
        printMatrix(multiplyMatrix(D, C));

	printf("I(2) = ");
	printMatrix(makeIdentityMatrix(2));

	printf("I*A =");
	printMatrix(multiplyMatrix(makeIdentityMatrix(2), A));


	printf("Transpose(C) = ");
	printMatrix(makeTransposeMatrix(C));

*/
	

	return 0;
}
