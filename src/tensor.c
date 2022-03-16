#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tensor.h"

TensorDimension *makeTensorDimension(int rank, int dimension);

TensorDimension *makeTensorDimension(int rank, int dimension) {
	TensorDimension *td = malloc(sizeof(TensorDimension));

	if (dimension == 1) {
		td->type = ten_terminal;
		td->data.indices = malloc(sizeof(int) * rank);

		return td;
	}

	td->type = ten_dim;
	td->data.dimension = malloc(sizeof(TensorDimension *) * rank);

	for (int i = 0; i < rank; i++) {
		td->data.dimension[i] = makeTensorDimension(rank, dimension - 1);
	}

	return td;
}

Tensor *makeTensor(int rank, int dimensions) {
	Tensor *tensor = malloc(sizeof(Tensor));

	tensor->numDimensions = dimensions;
	tensor->rank = rank;

	tensor->dimension = makeTensorDimension(rank, dimensions);

}
