#ifndef TENSOR_H
#define TENSOR_H

enum tensor_type {
	ten_dim,
	ten_terminal
} tensor_type;

typedef struct TensorDimension TensorDimension;

typedef struct TensorDimension {
	enum tensor_type type;
	union {
		TensorDimension **dimension;
		int *indices;
	} data;
} TensorDimension;

typedef struct Tensor {
        int numDimensions;
	int rank;
	TensorDimension *dimension;
} Tensor;

Tensor *makeTensor(int rank, int dimensions);

#endif
