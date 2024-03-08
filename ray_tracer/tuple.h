// tuple.h

#ifndef TUPLE_H
#define TUPLE_H

#include <stdbool.h>
#include <stdlib.h>
# include <math.h>
#include <stdio.h>

// Define the Tuple struct
typedef struct Tuple
{
    float x;
    float y;
    float z;
    float w; // 1 for point, 0 for vector
    bool (*is_point)(struct Tuple);
    bool (*equal)(struct Tuple, struct Tuple);
} Tuple;

// Function to check if the tuple is a point
bool is_point(struct Tuple t)
{
    return t.w == 1.0f;
}

bool equal(Tuple t1, Tuple t2)
{
    // only compare the x, y, and z values, see later if you need compare the w value as well.
    // if absolute value of w is same then return true
    return (fabs(t1.w) - fabs(t2.w) < 0.00001) && (t1.x == t2.x && t1.y == t2.y && t1.z == t2.z);
}

// whenever a new object is created call this function to initialize the is_point field
void init_tuple(Tuple *t, float x, float y, float z, float w)
{
    t->x = x;
    t->y = y;
    t->z = z;
    t->w = w;
    t->is_point = is_point;
    t->equal = equal;
}

Tuple Add(Tuple t1, Tuple t2)
{
    if (t1.w == 1.0f && t2.w == 1.0f) {
        // Raise an error or handle the error condition here
        // For example, you can print an error message and terminate the program
        printf("Error: Adding two points is not allowed.\n");
        exit(1);
    }
    Tuple result;
    init_tuple(&result, t1.x + t2.x, t1.y + t2.y, t1.z + t2.z, t1.w + t2.w);

    return result;
}

Tuple Subtract(Tuple t1, Tuple t2)
{
    if (t1.w == 0.0f && t2.w == 1.0f) {
        // Raise an error or handle the error condition here
        // For example, you can print an error message and terminate the program
        printf("Error: Subtracting a point from a vector is not allowed.\n");
        exit(1);
    }
    Tuple result;
    init_tuple(&result, t1.x - t2.x, t1.y - t2.y, t1.z - t2.z, t1.w - t2.w);

    return result;
}

void Negate(Tuple* t)
{

    init_tuple(t, -t->x, -t->y, -t->z, -t->w);
}

void ScalerMultiply(Tuple* t, float scalar)
{
    init_tuple(t, t->x * scalar, t->y * scalar, t->z * scalar, t->w * scalar);
}

void ScalerDivide(Tuple* t, float scalar)
{
    init_tuple(t, t->x / scalar, t->y / scalar, t->z / scalar, t->w / scalar);
}

Tuple Point(float x, float y, float z)
{
    Tuple t;
    init_tuple(&t, x, y, z, 1.0f);
    return t;
}

Tuple Vector(float x, float y, float z)
{
    Tuple t;
    init_tuple(&t, x, y, z, 0.0f);
    return t;
}

#endif /* TUPLE_H */
