#ifndef VECTOR_H
#define VECTOR_H

struct Vector {
        int size;
        int *data;
} Vector;

struct Vector *makeVector(int size);
struct Vector *copyVector(struct Vector *vector);

void printVector(struct Vector *v);
struct Vector *vectorAdd(struct Vector *a, struct Vector *b);
struct Vector *loadVector(char *file);
struct Vector *scalarMultiplyVector(struct Vector*vector, int scalar);


#endif
