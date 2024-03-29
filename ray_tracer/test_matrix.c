#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tuple.h"
#include <assert.h>

// global constants EPSILON
#define EPSILON 0.00001

void test_matrix()
{
    float numbers[16] = {
        1, 2, 3, 4,
        5.5, 6.5, 7.5, 8.5,
        9, 10, 11, 12,
        13.5, 14.5, 15.5, 16.5
    };
    Matrix *m = Matrix_(4, 4);
    SetMatrixValues(m, numbers);
    assert(m->data[0][0] == 1);
    assert(m->data[0][3] == 4);
    assert(m->data[1][0] == 5.5);
    assert(m->data[1][2] == 7.5);
    assert(m->data[2][2] == 11);
    assert(m->data[3][0] == 13.5);
    assert(m->data[3][2] == 15.5);
    printf("test_matrix passed\n");

    // Test 2x2 matrix
    float numbers2[4] = {
        -3, 5,
        1, -2
    };
    Matrix *m2 = Matrix_(2, 2);
    SetMatrixValues(m2, numbers2);
    assert(m2->data[0][0] == -3);
    assert(m2->data[0][1] == 5);
    assert(m2->data[1][0] == 1);
    assert(m2->data[1][1] == -2);
    printf("test_matrix2 passed\n");

    // Test 3x3 matrix
    float numbers3[9] = {
        -3, 5, 0,
        1, -2, -7,
        0, 1, 1
    };
    Matrix *m3 = Matrix_(3, 3);
    SetMatrixValues(m3, numbers3);
    assert(m3->data[0][0] == -3);
    assert(m3->data[1][1] == -2);
    assert(m3->data[2][2] == 1);
    printf("test_matrix3 passed\n");
}

void test_multiply_matrix()
{
    float numbers[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2
    };
    Matrix *m = Matrix_(4, 4);
    SetMatrixValues(m, numbers);

    float numbers2[16] = {
        -2, 1, 2, 3,
        3, 2, 1, -1,
        4, 3, 6, 5,
        1, 2, 7, 8
    };
    Matrix *m2 = Matrix_(4, 4);
    SetMatrixValues(m2, numbers2);

    float result[16] = {
        20, 22, 50, 48,
        44, 54, 114, 108,
        40, 58, 110, 102,
        16, 26, 46, 42
    };
    Matrix *expected = Matrix_(4, 4);
    SetMatrixValues(expected, result);

    Matrix *m3 = MultiplyMatrices(m, m2);
    assert(m3->rows == 4);
    assert(m3->cols == 4);
    for (int i = 0; i < m3->rows; i++)
    {
        for (int j = 0; j < m3->cols; j++)
        {
            assert(fabs(m3->data[i][j] - expected->data[i][j]) < EPSILON);
        }
    }
    assert(CompareMatrices(m3, expected));
    printf("test_multiply_matrix passed\n");

}

void test_multiply_matrix_tuple()
{
    float numbers[16] = {
        1, 2, 3, 4,
        2, 4, 4, 2,
        8, 6, 4, 1,
        0, 0, 0, 1
    };
    Matrix *m = Matrix_(4, 4);
    SetMatrixValues(m, numbers);

    Tuple t;
    init_tuple(&t, 1, 2, 3, 1);
    Tuple expected;
    init_tuple(&expected, 18, 24, 33, 1);
    Tuple *t2 = MultiplyMatrixByTuple(m, &t);
    assert(equal(*t2, expected));
    printf("test_multiply_matrix_tuple passed\n");
}

void test_identity_matrix()
{
    Matrix *m = IdentityMatrix(4);

    assert(m->rows == 4);
    assert(m->cols == 4);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            if (i == j)
            {
                assert(m->data[i][j] == 1);
            }
            else
            {
                assert(m->data[i][j] == 0);
            }
        }
    }
    printf("test_identity_matrix passed\n");

    // test that multiplying a matrix by the identity matrix returns the original matrix
    float numbers2[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 8, 7, 6,
        5, 4, 3, 2};
    Matrix *m2 = Matrix_(4, 4);
    SetMatrixValues(m2, numbers2);

    Matrix *m3 = MultiplyMatrices(m, m2);
    assert(CompareMatrices(m3, m2));
    printf("test_identity_matrix_multiplication passed\n");
}

void test_transpose_matrix()
{
    float numbers[16] = {
        0, 9, 3, 0,
        9, 8, 0, 8,
        1, 8, 5, 3,
        0, 0, 5, 8
    };
    Matrix *m = Matrix_(4, 4);
    SetMatrixValues(m, numbers);

    float result[16] = {
        0, 9, 1, 0,
        9, 8, 8, 0,
        3, 0, 5, 5,
        0, 8, 3, 8
    };
    Matrix *expected = Matrix_(4, 4);
    SetMatrixValues(expected, result);

    Matrix *m2 = TransposeMatrix(m);
    assert(m2->rows == 4);
    assert(m2->cols == 4);
    for (int i = 0; i < m2->rows; i++)
    {
        for (int j = 0; j < m2->cols; j++)
        {
            assert(fabs(m2->data[i][j] - expected->data[i][j]) < EPSILON);
        }
    }
    assert(CompareMatrices(m2, expected));
    printf("test_transpose_matrix passed\n");

}

void test_submatrix()
{
    float numbers[16] = {
        1, 5, 0,
        -3, 2, 7,
        0, 6, -3
    };
    Matrix *m = Matrix_(3, 3);
    SetMatrixValues(m, numbers);

    float result[4] = {
        -3, 2,
        0, 6
    };
    Matrix *expected = Matrix_(2, 2);
    SetMatrixValues(expected, result);

    Matrix *m2 = Submatrix(m, 0, 2);
    assert(m2->rows == 2);
    assert(m2->cols == 2);
    for (int i = 0; i < m2->rows; i++)
    {
        for (int j = 0; j < m2->cols; j++)
        {
            assert(fabs(m2->data[i][j] - expected->data[i][j]) < EPSILON);
        }
    }
    assert(CompareMatrices(m2, expected));
    printf("test_submatrix passed\n");

    float numbers2[16] = {
        1, 5, 0, 1,
        -3, 2, 7, 2,
        0, 6, -3, 3,
        1, 2, 3, 4
    };
    Matrix *m3 = Matrix_(4, 4);
    SetMatrixValues(m3, numbers2);

    float result2[9] = {
        -3, 2, 7,
        0, 6, -3,
        1, 2, 3
    };
    Matrix *expected2 = Matrix_(3, 3);
    SetMatrixValues(expected2, result2);

    Matrix *m4 = Submatrix(m3, 0, 3);
    assert(m4->rows == 3);
    assert(m4->cols == 3);
    for (int i = 0; i < m4->rows; i++)
    {
        for (int j = 0; j < m4->cols; j++)
        {
            assert(fabs(m4->data[i][j] - expected2->data[i][j]) < EPSILON);
        }
    }
    assert(CompareMatrices(m4, expected2));
    printf("test_submatrix2 passed\n");
}

void test_minor()
{
    float numbers[16] = {
        3, 5, 0,
        2, -1, -7,
        6, -1, 5
    };
    Matrix *m = Matrix_(3, 3);
    SetMatrixValues(m, numbers);
    Matrix *m2 = Submatrix(m, 1, 0);
    assert(Determinant(m2) == 25);
    assert(Minor(m, 1, 0) == 25);
    printf("test_minor passed\n");
}

void test_cofactor()
{
    float numbers[16] = {
        3, 5, 0,
        2, -1, -7,
        6, -1, 5
    };
    Matrix *m = Matrix_(3, 3);
    SetMatrixValues(m, numbers);
    assert(Minor(m, 0, 0) == -12);
    assert(Cofactor(m, 0, 0) == -12);
    assert(Minor(m, 1, 0) == 25);
    assert(Cofactor(m, 1, 0) == -25);
    printf("test_cofactor passed\n");

}

void test_determinant_of_larger_matrices()
{
    float numbers[16] = {
        1, 2, 6,
        -5, 8, -4,
        2, 6, 4};
    Matrix *m = Matrix_(3, 3);
    SetMatrixValues(m, numbers);
    assert(Cofactor(m, 0, 0) == 56);
    assert(Cofactor(m, 0, 1) == 12);
    assert(Cofactor(m, 0, 2) == -46);
    assert(Determinant(m) == -196);

    printf("test_determinant_of_larger_matrices passed\n");

    float numbers2[16] = {
        -2, -8, 3, 5,
        -3, 1, 7, 3,
        1, 2, -9, 6,
        -6, 7, 7, -9
    };
    Matrix *m2 = Matrix_(4, 4);
    SetMatrixValues(m2, numbers2);
    assert(Cofactor(m2, 0, 0) == 690);
    assert(Cofactor(m2, 0, 1) == 447);
    assert(Cofactor(m2, 0, 2) == 210);
    assert(Cofactor(m2, 0, 3) == 51);
    assert(Determinant(m2) == -4071);
    printf("test_determinant_of_larger_matrices2 passed\n");
}

void test_determinant_new()
{
    
    float numbers[4] = {
        1, 5,
        -3, 2};
    Matrix *m = Matrix_(2, 2);
    SetMatrixValues(m, numbers);
    assert(DeterminantNew(m) == 17);
    printf("test_determinant_new2 passed\n");

    float numbers2[9] = {
        1, 2, 6,
        -5, 8, -4,
        2, 6, 4};
    Matrix *m2 = Matrix_(3, 3);
    SetMatrixValues(m2, numbers2);
    assert(DeterminantNew(m2) == -196);
    printf("test_determinant_new3 passed\n");

    float numbers3[16] = {
        -2, -8, 3, 5,
        -3, 1, 7, 3,
        1, 2, -9, 6,
        -6, 7, 7, -9
    };
    Matrix *m3 = Matrix_(4, 4);
    SetMatrixValues(m3, numbers3);
    assert(DeterminantNew(m3) == -4071);
    printf("test_determinant_new4 passed\n");
}

void test_determinant()
{
    float numbers[16] = {
        1, 5,
        -3, 2};
    Matrix *m = Matrix_(2, 2);
    SetMatrixValues(m, numbers);
    assert(Determinant(m) == 17);
    printf("test_determinant2 passed\n");

    float numbers2[9] = {
        1, 2, 6,
        -5, 8, -4,
        2, 6, 4};
    Matrix *m2 = Matrix_(3, 3);
    SetMatrixValues(m2, numbers2);
    assert(Determinant(m2) == -196);
    printf("test_determinant3 passed\n");

    float numbers3[16] = {
        -2, -8, 3, 5,
        -3, 1, 7, 3,
        1, 2, -9, 6,
        -6, 7, 7, -9};
    Matrix *m3 = Matrix_(4, 4);
    SetMatrixValues(m3, numbers3);
    assert(Determinant(m3) == -4071);
    printf("test_determinant4 passed\n");
}

void test_invertible(){
    float numbers[16] = {
        6, 4, 4, 4,
        5, 5, 7, 6,
        4, -9, 3, -7,
        9, 1, 7, -6
    };
    Matrix *m = Matrix_(4, 4);
    SetMatrixValues(m, numbers);
    assert(Determinant(m) == -2120);
    assert(IsInvertible(m));
    printf("test_invertible passed\n");

    float numbers2[16] = {
        -4, 2, -2, -3,
        9, 6, 2, 6,
        0, -5, 1, -5,
        0, 0, 0, 0
    };
    Matrix *m2 = Matrix_(4, 4);
    SetMatrixValues(m2, numbers2);
    assert(Determinant(m2) == 0);
    assert(!IsInvertible(m2));
    printf("test_invertible2 passed\n");

}

void test_inverse()
{
    float numbers[16] = {
        -5, 2, 6, -8,
        1, -5, 1, 8,
        7, 7, -6, -7,
        1, -3, 7, 4
    };
    Matrix *m = Matrix_(4, 4);
    SetMatrixValues(m, numbers);
    Matrix *m2 = Inverse(m);
    assert(Determinant(m) == 532);
    assert(Cofactor(m, 2, 3) == -160);
    assert(m2->data[3][2] == -160.0f / 532.0f);
    assert(Cofactor(m, 3, 2) == 105);
    assert(m2->data[2][3] == 105.0f / 532);

    Matrix *expected = Matrix_(4, 4);
    expected = Matrix_(4, 4);
    float result_nums[16] = {
        0.21805, 0.45113, 0.24060, -0.04511,
        -0.80827, -1.45677, -0.44361, 0.52068,
        -0.07895, -0.22368, -0.05263, 0.19737,
        -0.52256, -0.8139, -0.30075, 0.30639
    };
    SetMatrixValues(expected, result_nums);

    assert(CompareMatrices(m2, expected));
    printf("test_inverse passed\n");
}

void test_invererse_rule()
{
    float numbers[16] = {
        3, -9, 7, 3,
        3, -8, 2, -9,
        -4, 4, 4, 1,
        -6, 5, -1, 1
    };
    Matrix *a = Matrix_(4, 4);
    SetMatrixValues(a, numbers);
    float numbers2[16] = {
        8, 2, 2, 2,
        3, -1, 7, 0,
        7, 0, 5, 4,
        6, -2, 0, 5
    };
    Matrix *b = Matrix_(4, 4);
    SetMatrixValues(b, numbers2);
    Matrix *c = MultiplyMatrices(a, b);
    Matrix *b_i = Inverse(b);
    Matrix *m5 = MultiplyMatrices(c, b_i);
    assert(CompareMatrices(m5, a));
    printf("test_invererse_rule passed\n");

}

int main () {
    test_matrix();
    test_multiply_matrix();
    test_multiply_matrix_tuple();
    test_identity_matrix();
    test_transpose_matrix();
    test_submatrix();
    test_minor();
    test_cofactor();
    test_determinant_of_larger_matrices();
    test_determinant_new(); 
    test_determinant();
    test_invertible();
    test_inverse();
    test_invererse_rule();
    return 0;
}