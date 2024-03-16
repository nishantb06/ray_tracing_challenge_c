#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "tuple.h"
#include "string.h"
#include <stdio.h>

// global constants EPSILON
#define EPSILON 0.00001

//declare DeterminantNew function

typedef struct Matrix
{   
    int rows;
    int cols;
    float **data;
} Matrix;

float DeterminantNew(Matrix *m);

Matrix* Matrix_(int rows, int cols)
{
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));

    matrix->rows = rows;
    matrix->cols = cols;
    // Allocate memory for array of pointers to rows
    matrix->data = (float **)malloc(rows * sizeof(float *));
    if (matrix->data == NULL)
    {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each row and initialize to zero
    for (int i = 0; i < rows; i++)
    {
        matrix->data[i] = (float *)calloc(cols, sizeof(float));
        if (matrix->data[i] == NULL)
        {
            printf("Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }

    return matrix;
}

void SetMatrixValues(Matrix *matrix, float *values)
{   
    // length of the values array should be equal to the number of elements in the matrixs

    int k = 0;
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            matrix->data[i][j] = values[k];
            k++;
        }
    }
}

bool CompareMatrices(Matrix *a, Matrix *b)
{
    if (a->rows != b->rows || a->cols != b->cols)
    {
        return false;
    }
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            if (fabs(a->data[i][j] - b->data[i][j]) > EPSILON)
            {
                return false;
            }
        }
    }
    return true;
}

void PrintMatrix(Matrix* matrix)
{
    // Print the matrix in a readable format
    for (int i = 0; i < matrix->rows; i++)
    {   
        printf("| ");
        for (int j = 0; j < matrix->cols; j++)
        {
            printf("%f | ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

Matrix* MultiplyMatrices(Matrix *a, Matrix *b)
{
    // Check if the matrices can be multiplied
    if (a->cols != b->rows)
    {
        printf("Matrices cannot be multiplied\n");
        exit(EXIT_FAILURE);
    }

    // Create a result matrix with dimensions a->rows x b->cols
    Matrix *result = Matrix_(a->rows, b->cols);

    // Multiply the matrices
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            // Compute the dot product of row i from matrix a and column j from matrix b
            float sum = 0.0;
            for (int k = 0; k < a->cols; k++)
            {
                sum += a->data[i][k] * b->data[k][j];
            }
            // Assign the result to the corresponding element in the result matrix
            result->data[i][j] = sum;
        }
    }

    return result;
}

Tuple* MultiplyMatrixByTuple(Matrix *a, Tuple *b)
{
    // Check if the matrix and tuple can be multiplied
    if (a->cols != 4)
    {
        printf("Matrix and tuple cannot be multiplied\n");
        exit(EXIT_FAILURE);
    }

    // Create a result tuple
    Tuple *result = (Tuple *)malloc(sizeof(Tuple));
    init_tuple(result, 0.0f, 0.0f, 0.0f, 0.0f);

    // Multiply the matrix and tuple
    for (int i = 0; i < a->rows; i++)
    {
        float sum = 0.0;
        for (int j = 0; j < a->cols; j++)
        {
            sum += a->data[i][j] * b->data[j];
        }
        result->data[i] = sum;
    }
    init_tuple(result, result->data[0], result->data[1], result->data[2], result->data[3]);

    return result;

}

Matrix* IdentityMatrix(int size)
{
    Matrix *matrix = Matrix_(size, size);
    for (int i = 0; i < size; i++)
    {
        matrix->data[i][i] = 1.0f;
    }
    return matrix;
}

Matrix* TransposeMatrix(Matrix *matrix)
{
    Matrix *result = Matrix_(matrix->cols, matrix->rows);
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            result->data[j][i] = matrix->data[i][j];
        }
    }
    return result;
}

float Determinant2x2(Matrix *matrix)
{
    if (matrix->rows != 2 || matrix->cols != 2)
    {
        printf("Matrix is not 2x2\n");
        printf("Matrix of size %d x %d\n", matrix->rows, matrix->cols);
        exit(EXIT_FAILURE);
    }
    return matrix->data[0][0] * matrix->data[1][1] - matrix->data[0][1] * matrix->data[1][0];
}

Matrix *Submatrix(Matrix *matrix, int row, int col)
{
    Matrix *result = Matrix_(matrix->rows - 1, matrix->cols - 1);
    int result_row = 0;
    for (int i = 0; i < matrix->rows; i++)
    {
        if (i == row)
        {
            continue;
        }
        int result_col = 0;
        for (int j = 0; j < matrix->cols; j++)
        {
            if (j == col)
            {
                continue;
            }
            result->data[result_row][result_col] = matrix->data[i][j];
            result_col++;
        }
        result_row++;
    }
    return result;
}

float Minor(Matrix *matrix, int row, int col)
{
    return DeterminantNew(Submatrix(matrix, row, col));
}

float Cofactor(Matrix *matrix, int row, int col)
{
    float minor = Minor(matrix, row, col);
    if ((row + col) % 2 != 0)
    {
        return -minor;
    }
    return minor;
}

float DeterminantNew(Matrix* m)
{
    if (m->rows != m->cols)
    {
        printf("Matrix is not square\n");
        exit(EXIT_FAILURE);
    }
    if (m->rows == 2)
    {
        return m->data[0][0] * m->data[1][1] - m->data[0][1] * m->data[1][0];
    }
    float sum = 0.0;
    for (int i = 0; i < m->cols; i++)
    {
        sum += m->data[0][i] * Cofactor(m, 0, i);
    }
    return sum;
}

float Determinant3x3(Matrix *matrix)
{
    if (matrix->rows != 3 || matrix->cols != 3)
    {
        printf("Matrix is not 3x3\n");
        exit(EXIT_FAILURE);
    }
    return matrix->data[0][0] * (matrix->data[1][1] * matrix->data[2][2] - matrix->data[1][2] * matrix->data[2][1]) -
           matrix->data[0][1] * (matrix->data[1][0] * matrix->data[2][2] - matrix->data[1][2] * matrix->data[2][0]) +
           matrix->data[0][2] * (matrix->data[1][0] * matrix->data[2][1] - matrix->data[1][1] * matrix->data[2][0]);
}

float Determinant4x4(Matrix *matrix)
{
    if (matrix->rows != 4 || matrix->cols != 4)
    {
        printf("Matrix is not 4x4\n");
        exit(EXIT_FAILURE);
    }
    float a = matrix->data[0][0];
    float b = matrix->data[0][1];
    float c = matrix->data[0][2];
    float d = matrix->data[0][3];
    float e = matrix->data[1][0];
    float f = matrix->data[1][1];
    float g = matrix->data[1][2];
    float h = matrix->data[1][3];
    float i = matrix->data[2][0];
    float j = matrix->data[2][1];
    float k = matrix->data[2][2];
    float l = matrix->data[2][3];
    float m = matrix->data[3][0];
    float n = matrix->data[3][1];
    float o = matrix->data[3][2];
    float p = matrix->data[3][3];

    return a * Determinant3x3(Submatrix(matrix, 0, 0)) - b * Determinant3x3(Submatrix(matrix, 0, 1)) +
           c * Determinant3x3(Submatrix(matrix, 0, 2)) - d * Determinant3x3(Submatrix(matrix, 0, 3));
}

float Determinant(Matrix *matrix)
{
    if (matrix->rows != matrix->cols)
    {
        printf("Matrix is not square");
        exit(EXIT_FAILURE);
    }
    if (matrix->rows == 2)
    {
        return Determinant2x2(matrix);
    }

    if (matrix->rows == 3)
    {
        return Determinant3x3(matrix);
    }

    if (matrix->rows == 4)
    {
        return Determinant4x4(matrix);
    }

    else {
        printf("Matrix is not 2x2, 3x3 or 4x4\n");
        exit(EXIT_FAILURE);
    }
}

bool IsInvertible(Matrix *matrix)
{
    return Determinant(matrix) != 0;
}

Matrix* Inverse(Matrix *matrix)
{
    if (!IsInvertible(matrix))
    {
        printf("Matrix is not invertible\n");
        exit(EXIT_FAILURE);
    }
    Matrix *result = Matrix_(matrix->rows, matrix->cols);
    float det = Determinant(matrix);
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            float c = Cofactor(matrix, i, j);
            result->data[j][i] = c / det;
        }
    }
    return result;
}

#endif