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

int main()
{
    test_translation();
    test_scaling();
    return 0;
}