#include "tuple.h"
#include <assert.h>
#include <stdio.h>

void test_is_point() {
    Tuple point = {1.0f, 2.0f, 3.0f, 1.0f, is_point}; // A point
    assert(point.is_point);
}

void test_is_vector() {
    Tuple vector = {1.0f, 2.0f, 3.0f, 0.0f, is_point};
    printf("Is point: %d\n", vector.is_point(vector)); // Output: 0 (false)
    assert(!vector.is_point(vector));
}

void test_init_tuple() {
    Tuple t1;
    init_tuple(&t1, 1.0f, 2.0f, 3.0f, 1.0f); // A point
    printf("Is point: %d\n", t1.is_point(t1)); // Output: 1 (true)
    assert(t1.is_point(t1));
}

void test_point() {
    Tuple point = Point(4.0f, -4.0f, 3.0f);
    assert (point.x == 4.0f);
    assert (point.y == -4.0f);
    assert (point.z == 3.0f);
    assert (point.w == 1.0f);
    assert(point.is_point(point));
    printf("test_point passed\n");
}

void test_vector() {
    Tuple vector = Vector(4.0f, -4.0f, 3.0f);
    assert (vector.x == 4.0f);
    assert (vector.y == -4.0f);
    assert (vector.z == 3.0f);
    assert (vector.w == 0.0f);
    assert(!vector.is_point(vector));
    printf("test_vector passed\n");
}

void test_equal() {
    Tuple t1 = Point(1.0f, 2.0f, 3.0f);
    Tuple t2 = Point(1.0f, 2.0f, 3.0f);
    Tuple t3 = Vector(1.0f, 2.0f, 3.0f);
    assert(equal(t1, t2));
    assert(t1.equal(t1, t2));
    assert(!equal(t1, t3));
    assert(!t1.equal(t1, t3));
    printf("test_equal passed\n");
}

void test_add() {
    Tuple t1 = Point(3.0f, -2.0f, 5.0f);
    Tuple t2 = Vector(-2.0f, 3.0f, 1.0f);
    Tuple t3 = Add(t1, t2);
    assert(equal(t3, Point(1.0f, 1.0f, 6.0f)));

    // check that it doesn't modify the original tuples
    assert(equal(t1, Point(3.0f, -2.0f, 5.0f)));
    assert(equal(t2, Vector(-2.0f, 3.0f, 1.0f)));

    // assert that adding two points is not allowed

    printf("test_add passed\n");
}

void test_subtract() {
    Tuple t1 = Point(3.0f, 2.0f, 1.0f);
    Tuple t2 = Point(5.0f, 6.0f, 7.0f);
    Tuple t3 = Subtract(t1, t2);
    assert(equal(t3, Vector(-2.0f, -4.0f, -6.0f)));

    // check that it doesn't modify the original tuples
    assert(equal(t1, Point(3.0f, 2.0f, 1.0f)));
    assert(equal(t2, Point(5.0f, 6.0f, 7.0f)));

    // assert that subtracting two vectors is allowed
    Tuple t4 = Vector(3.0f, 2.0f, 1.0f);
    Tuple t5 = Vector(5.0f, 6.0f, 7.0f);
    Tuple t6 = Subtract(t4, t5);
    assert(equal(t6, Vector(-2.0f, -4.0f, -6.0f)));

    // assert that subtracting a point from a vector is allowed
    Tuple t7 = Point(3.0f, 2.0f, 1.0f);
    Tuple t8 = Vector(5.0f, 6.0f, 7.0f);
    Tuple t9 = Subtract(t7, t8);
    assert(equal(t9, Point(-2.0f, -4.0f, -6.0f)));

    printf("test_subtract passed\n");
}

void test_negate() {
    Tuple t1 = Point(1.0f, -2.0f, 3.0f);
    Negate(&t1);
    assert(equal(t1, Point(-1.0f, 2.0f, -3.0f)));

    printf("test_negate passed\n");
}

void test_scaler_multiply() {

    Tuple t1,output;
    init_tuple(&output, 3.5f, -7.0f, 10.5f, -14.0f);
    init_tuple(&t1, 1.0f, -2.0f, 3.0f, 4.0f);
    ScalerMultiply(&t1, 3.5f);
    assert(equal(t1, output));

    printf("test_multiply passed\n");
}

void test_scaler_divide() {
    Tuple t1,output;
    init_tuple(&output, 0.5f, -1.0f, 1.5f, -2.0f);
    init_tuple(&t1, 1.0f, -2.0f, 3.0f, 4.0f);
    ScalerDivide(&t1, 2.0f);
    assert(equal(t1, output));

    printf("test_divide passed\n");
}

void test_magnitude(){
    Tuple t1;
    init_tuple(&t1, 1.0f, 0.0f, 0.0f, 0.0f);
    assert(Magnitude(&t1) == 1.0f);

    init_tuple(&t1, 0.0f, 1.0f, 0.0f, 0.0f);
    assert(Magnitude(&t1) == 1.0f);

    init_tuple(&t1, 0.0f, 0.0f, 1.0f, 0.0f);
    assert(Magnitude(&t1) == 1.0f);

    init_tuple(&t1, 1.0f, 2.0f, 3.0f, 0.0f);
    assert(fabs(Magnitude(&t1) - sqrt(14.0f)) < 0.0001f);

    init_tuple(&t1, -1.0f, -2.0f, -3.0f, 0.0f);
    assert(fabs(Magnitude(&t1) - sqrt(14.0f)) < 0.0001f);

    printf("test_magnitude passed\n");

}

void test_dot_product() {
    Tuple t1 = Vector(1.0f, 2.0f, 3.0f);
    Tuple t2 = Vector(2.0f, 3.0f, 4.0f);
    assert(DotProduct(&t1, &t2) == 20.0f);

    printf("test_dot_product passed\n");
}

void test_cross_product() {
    Tuple t1 = Vector(1.0f, 2.0f, 3.0f);
    Tuple t2 = Vector(2.0f, 3.0f, 4.0f);
    Tuple t3 = CrossProduct(&t1, &t2);
    assert(equal(t3, Vector(-1.0f, 2.0f, -1.0f)));

    printf("test_cross_product passed\n");
}

int main() {
    test_is_point();
    test_is_vector();
    test_init_tuple();
    test_point();
    test_vector();
    test_equal();
    test_add();
    test_subtract();
    test_negate();
    test_scaler_multiply();
    test_scaler_divide();
    test_magnitude();
    test_dot_product();
    test_cross_product();
    return 0;
}

// gcc test_tuple.c -o test_tuple
// ./test_tuple