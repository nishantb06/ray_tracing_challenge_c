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

typedef struct Matrix
{   
    int rows;
    int cols;
    float **data;
} Matrix;

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

Matrix* MultiplyMatrixByTuple(Matrix *a, Tuple *b)
{
    // Check if the matrix and tuple can be multiplied
    if (a->cols != 4)
    {
        printf("Matrix and tuple cannot be multiplied\n");
        exit(EXIT_FAILURE);
    }

    // Create a result tuple
    Tuple *result = Tuple_(0, 0, 0, 0);

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

    return result;
}

#endif