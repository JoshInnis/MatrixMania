
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "matrix.h"

struct Vector {
	int size;
	int *data;
} Vector;

//#typedef bool int;
#define true 1
#define false 0

struct Vector *makeVector(int size);
struct Vector *copyVector(struct Vector *vector);
 
struct Vector *makeVector(int size) {
        struct Vector *A = malloc(sizeof(Vector));

        A->size = size;

        A->data = malloc(sizeof(int *) * size);

        return A;
}

void printVector(struct Vector *v) {
        printf("[\n");

        for (int i = 0; i < v->size; i ++) {

        	printf("%i\n", v->data[i]);

        }

        printf("]\n");
}

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

struct Vector *loadVector(char *file) {
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        fp = fopen(file, "r");
        int size;

        read = getline(&line, &len, fp);
        sscanf(line, "%i", &size);

        struct Vector *vect = makeVector(size);

        int cur_row = 0;
        while ((read = getline(&line, &len, fp)) != -1) {
                int cur_col = 0;

                char *token;
                char delim[2] = " ";
                token = strtok(line, delim);

                while( token != NULL ) {
                        vect->data[cur_row] = atoi(token);

                        token = strtok(NULL, delim);

                        cur_col++;
                }
                cur_row++;
        }

        return vect;
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

struct Vector *copyVector(struct Vector *vector) {
        struct Vector *new_vector = makeVector(vector->size);

        for (int i = 0; i < vector->size; i++) {
        	new_vector->data[i] = vector->data[i];
        }

        return new_vector;
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
