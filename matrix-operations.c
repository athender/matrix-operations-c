/* This program can perform the following matrix operations:
- Multiply a scalar by a multiple
- Add two matrices
- Multiply two matrices

Some useful applications for school.*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <matrix-operations.h>

/*
* Function: createMatrix creates a matrix with size and content given by the user.
* Variables: loop counters - i, j; matr - pointer to matrix
*/
struct matrix *createMatrix(int rows, int columns) {

    struct matrix *matr = malloc(sizeof(struct matrix));

    if (matr == NULL){
        return NULL;
    }

    matr -> numRows = rows;
    matr -> numColumns = columns;
    matr -> elements = malloc(sizeof(float*) * rows);

    if (matr -> elements == NULL){
        free(matr);
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        matr -> elements[i] = malloc(sizeof(float) * columns);
        if (matr->elements[i] == NULL){
            for (int j = i-1; j >= 0; j--){
                free(matr -> elements[j]);
            }
            free(matr->elements);
            free(matr);
            return NULL;
        }

        for (int j = 0; j < columns; j++) {
            matr -> elements[i][j] = 0;
        }
    }

    return matr;
}

/*
* Function: fillMatrix fills a given matrix with elements prompted from the user.
* Variables: i, j - loop counters
*/
struct matrix *fillMatrix(struct matrix *matr, int rows, int columns) {
    for (int i = 0; i < matr -> numRows; i++) {
        for (int j = 0; j < matr -> numColumns; j++) {
            printf("Enter element %d, %d: ", i+1, j+1);
            scanf("%f", &(matr -> elements[i][j]));
        }
    }
    return matr;
}

/*
* Function: printMatrix prints a matrix passed to it.
* Variables: i, j - loop counters
*/
void printMatrix(const struct matrix* matr) {

    for (int i = 0; i < matr -> numRows; i++) {

        for (int j = 0; j < matr -> numColumns; j++) {
            printf("%f ", matr -> elements[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/*
* Function: multByScalar multiplies a given matrix by a given scalar.
* Variables: i, j - loop counters; newMatrix - result matrix of scalar multiplication
*/

struct matrix *multByScalar (float scalar, const struct matrix* matr) {

    struct matrix *newMatrix = createMatrix(matr -> numRows, matr -> numColumns);
    for (int i = 0; i < matr -> numRows; i++) {
        for (int j = 0; j < matr -> numColumns; j++) {
    
            newMatrix -> elements[i][j] = scalar * matr -> elements[i][j];
        }
    }
    return newMatrix;
}

/*
* Function: multMatrices gives the matrix product of two given matrices.
* Variables: i, j, k - loop counters; matrixProduct - product of given matrices
*/
struct matrix *multMatrices (const struct matrix *matrixA, const struct matrix *matrixB) {
    
    if (matrixA -> numColumns != matrixB -> numRows){
        printf("Matrices not of correct size.");
        return NULL;
    }

    struct matrix *matrixProduct = createMatrix(matrixA -> numRows, matrixB -> numColumns);

    for (int i = 0; i < matrixProduct -> numRows; i++) {
        for (int j = 0; j < matrixA -> numColumns; j++) {
            for (int k = 0; k < matrixA -> numColumns; k++) {

                matrixProduct -> elements[i][j] += (matrixA -> elements[i][k]) * (matrixB -> elements[k][j]);
            }
        }
    }
    return matrixProduct;
}

/*
* Function: addMatrices gives the sum of two given matrices.
* Variables: i, j - loop counters; matrixSum - sum of given matrices
*/
struct matrix *addMatrices (const struct matrix *matrixA, const struct matrix *matrixB) {
    if ((matrixA -> numRows != matrixB -> numRows) || (matrixA -> numColumns != matrixB -> numColumns)){
        printf("Matrices not of correct size.");
        return NULL;
    }

    struct matrix *matrixSum = createMatrix (matrixA -> numRows, matrixB -> numColumns);
    
    for (int i = 0; i < matrixSum -> numRows; i++) {
        for (int j = 0; j < matrixSum -> numColumns; j++) {
            matrixSum -> elements[i][j] = (matrixA -> elements[i][j]) + (matrixB -> elements[i][j]);
        }
    }

    return matrixSum;
}


/*
* Variables: origMatrix - first matrix input, newMatrix - second input matrix (for adding), blankMatrix - temp matrix for operations, resultMatrix - matrix with  result of applied operation
*/

int main(){
    struct matrix *origMatrix, *newMatrix, *blankMatrix, *resultMatrix;
    int rows, columns;
    float scalar;

    // Test for functions:
    // 1 - Reading and printing a matrix
    printf("Enter the number of rows in your matrix: ");
    scanf("%d", &rows);
    printf("Enter the number of columns in your matrix: ");
    scanf("%d", &columns);

    blankMatrix = createMatrix(rows, columns);
    origMatrix = fillMatrix(blankMatrix, rows, columns);
    printf("\n");
    printf("Original matrix: \n");
    printMatrix(origMatrix);
    
    // 2 - Multiplying a matrix by a scalar
    printf("Enter the scalar you want to multiply the matrix by: ");
    scanf("%f", &scalar);
    resultMatrix = multByScalar(scalar, origMatrix);

    printf("\n");
    printf("Scaled matrix: \n");
    printMatrix(resultMatrix);

    // 3 - Adding two matrices
    printf("Enter the number of rows in your second matrix: ");
    scanf("%d", &rows);
    printf("Enter the number of columns in your second matrix: ");
    scanf("%d", &columns);
    blankMatrix = createMatrix(rows, columns);
    newMatrix = fillMatrix(blankMatrix, rows, columns);

    resultMatrix = addMatrices(origMatrix, newMatrix);
    printf("Matrix sum: \n");
    printMatrix(resultMatrix);

    // 4 - Multiply two matrices
    printf("Enter the number of rows in your second matrix: ");
    scanf("%d", &rows);
    printf("Enter the number of columns in your second matrix: ");
    scanf("%d", &columns);
    blankMatrix = createMatrix(rows, columns);
    newMatrix = fillMatrix(blankMatrix, rows, columns);

    resultMatrix = multMatrices(origMatrix, newMatrix);
    printf("Matrix product: \n");
    printMatrix(resultMatrix);

    return 0;
}
