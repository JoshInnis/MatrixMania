#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"


Vector *copyVector(Vector *vector) {
        Vector *new_vector = makeVector(vector->size);

        for (int i = 0; i < vector->size; i++) {
                new_vector->data[i] = vector->data[i];
        }

        return new_vector;
}

Vector *makeVector(int size) {
        Vector *A = malloc(sizeof(Vector));

        A->size = size;

        A->data = malloc(sizeof(int *) * size);

        return A;
}

void printVector(Vector *v) {
        printf("[\n");

        for (int i = 0; i < v->size; i ++) {

                printf("%i\n", v->data[i]);

        }

        printf("]\n");
}


Vector *vectorAdd(Vector *a, Vector *b) {
        Vector *v = copyVector(a);


        for (int i = 0; i < v->size; i++) {
                v->data[i] += b->data[i];
        }

        return v;
}

Vector *loadVector(char *file) {
        FILE * fp;
        char * line = NULL;
        size_t len = 0;
        ssize_t read;
        fp = fopen(file, "r");
        int size;

        read = getline(&line, &len, fp);
        sscanf(line, "%i", &size);

        Vector *vect = makeVector(size);

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

