#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "tuple.h"
#include "matrix.h"
#include "transformation.h"

void test_translation()
{
    Matrix *transform = Translation(5, -3, 2);
    Tuple p = Point(-3, 4, 5);
    Tuple *p2 = MultiplyMatrixByTuple(transform, &p);
    Tuple expected = Point(2, 1, 7);
    assert(equal(*p2, expected));
    printf("Test translation passed\n");

    Matrix *inv = Inverse(transform);
    Tuple *p3 = MultiplyMatrixByTuple(inv, &p);
    Tuple expected2 = Point(-8, 7, 3);
    assert(equal(*p3, expected2));
    printf("Test inverse translation passed\n");

    // translation does not affect vectors
    Tuple v = Vector(-3, 4, 5);
    Tuple *v2 = MultiplyMatrixByTuple(transform, &v);
    assert(equal(*v2, v));
    printf("Test translation does not affect vectors passed\n");

}

void test_scaling()
{
    Tuple p = Point(-4, 6, 8);
    Matrix *transform = Scaling(2, 3, 4);
    Tuple *p2 = MultiplyMatrixByTuple(transform, &p);
    Tuple expected = Point(-8, 18, 32);
    assert(equal(*p2, expected));
    printf("Test scaling passed\n");

    Tuple v = Vector(-4, 6, 8);
    Matrix *transform2 = Scaling(2, 3, 4);
    Tuple *v2 = MultiplyMatrixByTuple(transform2, &v);
    Tuple expected2 = Vector(-8, 18, 32);
    assert(equal(*v2, expected2));
    printf("Test scaling does affect vectors passed\n");

    Matrix *inv = Inverse(transform);
    Tuple *p3 = MultiplyMatrixByTuple(inv, &p);
    Tuple expected3 = Point(-2, 2, 2);
    assert(equal(*p3, expected3));
    printf("Test inverse scaling passed\n");

    // reflection is scaling by a negative value
    Matrix *transform3 = Scaling(-1, 1, 1);
    Tuple p4 = Point(2, 3, 4);
    Tuple *p5 = MultiplyMatrixByTuple(transform3, &p4);
    Tuple expected4 = Point(-2, 3, 4);
    assert(equal(*p5, expected4));
    printf("Test reflection passed\n");
}

void test_rotation_x()
{
    Tuple p = Point(0, 1, 0);
    Matrix *half_quarter = RotationX(M_PI / 4);
    Matrix *full_quarter = RotationX(M_PI / 2);
    Tuple *p2 = MultiplyMatrixByTuple(half_quarter, &p);
    Tuple *p3 = MultiplyMatrixByTuple(full_quarter, &p);
    Tuple expected = Point(0, sqrt(2)/2, sqrt(2)/2);
    Tuple expected2 = Point(0, 0, 1);
    assert(equal(*p2, expected));
    assert(equal(*p3, expected2));
    printf("Test rotation x passed\n");

    // inverse of an x rotation rotates in the opposite direction
    Matrix *inv = Inverse(half_quarter);
    Tuple *p4 = MultiplyMatrixByTuple(inv, &p);
    Tuple expected3 = Point(0, sqrt(2)/2, -sqrt(2)/2);
    assert(equal(*p4, expected3));
    printf("Test inverse rotation x passed\n");

}

void test_rotation_y()
{
    Tuple p = Point(0, 0, 1);
    Matrix *half_quarter = RotationY(M_PI / 4);
    Matrix *full_quarter = RotationY(M_PI / 2);
    Tuple *p2 = MultiplyMatrixByTuple(half_quarter, &p);
    Tuple *p3 = MultiplyMatrixByTuple(full_quarter, &p);
    Tuple expected = Point(sqrt(2)/2, 0, sqrt(2)/2);
    Tuple expected2 = Point(1, 0, 0);
    assert(equal(*p2, expected));
    assert(equal(*p3, expected2));
    printf("Test rotation y passed\n");

    // inverse of an y rotation rotates in the opposite direction
    Matrix *inv = Inverse(half_quarter);
    Tuple *p4 = MultiplyMatrixByTuple(inv, &p);
    Tuple expected3 = Point(-sqrt(2)/2, 0, sqrt(2)/2);
    assert(equal(*p4, expected3));
    printf("Test inverse rotation y passed\n");

}

void test_rotation_z()
{
    Tuple p = Point(0, 1, 0);
    Matrix *half_quarter = RotationZ(M_PI / 4);
    Matrix *full_quarter = RotationZ(M_PI / 2);
    Tuple *p2 = MultiplyMatrixByTuple(half_quarter, &p);
    Tuple *p3 = MultiplyMatrixByTuple(full_quarter, &p);
    Tuple expected = Point(-sqrt(2)/2, sqrt(2)/2, 0);
    Tuple expected2 = Point(-1, 0, 0);
    assert(equal(*p2, expected));
    assert(equal(*p3, expected2));
    printf("Test rotation z passed\n");

    // inverse of an z rotation rotates in the opposite direction
    Matrix *inv = Inverse(half_quarter);
    Tuple *p4 = MultiplyMatrixByTuple(inv, &p);
    Tuple expected3 = Point(sqrt(2)/2, sqrt(2)/2, 0);
    assert(equal(*p4, expected3));
    printf("Test inverse rotation z passed\n");

}

void test_shearing()
{
    Matrix *transform = Shearing(1, 0, 0, 0, 0, 0);
    Tuple p = Point(2, 3, 4);
    Tuple *p2 = MultiplyMatrixByTuple(transform, &p);
    Tuple expected = Point(5, 3, 4);
    assert(equal(*p2, expected));
    printf("Test shearing 1 passed\n");

    Matrix *transform2 = Shearing(0, 1, 0, 0, 0, 0);
    Tuple p3 = Point(2, 3, 4);
    Tuple *p4 = MultiplyMatrixByTuple(transform2, &p3);
    Tuple expected2 = Point(6, 3, 4);
    assert(equal(*p4, expected2));
    printf("Test shearing 2 passed\n");

    Matrix *transform3 = Shearing(0, 0, 1, 0, 0, 0);
    Tuple p5 = Point(2, 3, 4);
    Tuple *p6 = MultiplyMatrixByTuple(transform3, &p5);
    Tuple expected3 = Point(2, 5, 4);
    assert(equal(*p6, expected3));
    printf("Test shearing 3 passed\n");

    Matrix *transform4 = Shearing(0, 0, 0, 1, 0, 0);
    Tuple p7 = Point(2, 3, 4);
    Tuple *p8 = MultiplyMatrixByTuple(transform4, &p7);
    Tuple expected4 = Point(2, 7, 4);
    assert(equal(*p8, expected4));
    printf("Test shearing 4 passed\n");

    Matrix *transform5 = Shearing(0, 0, 0, 0, 1, 0);
    Tuple p9 = Point(2, 3, 4);
    Tuple *p10 = MultiplyMatrixByTuple(transform5, &p9);
    Tuple expected5 = Point(2, 3, 6);
    assert(equal(*p10, expected5));
    printf("Test shearing 5 passed\n");

    Matrix *transform6 = Shearing(0, 0, 0, 0, 0, 1);
    Tuple p11 = Point(2, 3, 4);
    Tuple *p12 = MultiplyMatrixByTuple(transform6, &p11);
    Tuple expected6 = Point(2, 3, 7);
    assert(equal(*p12, expected6));
    printf("Test shearing 6 passed\n");
}

int main()
{
    test_translation();
    test_scaling();
    test_rotation_x();
    test_rotation_y();
    test_rotation_z();
    test_shearing();
    return 0;
}