#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vector {
        int size;
        int *data;
} Vector;

Vector *makeVector(int size);
Vector *copyVector(struct Vector *vector);

void printVector(Vector *v);
Vector *vectorAdd(Vector *a, Vector *b);
Vector *loadVector(char *file);
Vector *scalarMultiplyVector(Vector*vector, int scalar);


#endif
