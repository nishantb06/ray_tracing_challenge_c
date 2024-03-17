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

int main()
{
    test_translation();
    return 0;
}