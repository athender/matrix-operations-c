#include <stdio.h>

/*
* Structure: Defines a matrix with size numRows x numColumns and with entries pointed to by elements.
*/
struct matrix {
    int numRows;
    int numColumns;
    float **elements;
};

struct matrix *createMatrix(int rows, int columns);
struct matrix *fillMatrix(struct matrix *matr, int rows, int columns);
void printMatrix(const struct matrix* matr);
struct matrix *multByScalar(float scalar, const struct matrix* matr);
struct matrix *multMatrices(const struct matrix *matrixA, const struct matrix *matrixB);
struct matrix *addMatrices(const struct matrix *matrixA, const struct matrix *matrixB);