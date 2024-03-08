// main.c

#include <stdio.h>
#include "tuple.h"

int main()
{
    // Example usage
    Tuple point = {1.0f, 2.0f, 3.0f, 0.0f, is_point};  // A point
    Tuple vector = {4.0f, 5.0f, 6.0f, 1.0f, is_point}; // A vector
    Tuple t1;

    init_tuple(&t1, 1.0f, 2.0f, 3.0f, 0.0f); // A point
    printf("Is point: %d\n", t1.is_point(t1));       // Output: 1 (true)
    printf("Is point: %d\n", point.is_point(point));   // Output: 1 (true)
    printf("Is point: %d\n", vector.is_point(vector)); // Output: 0 (false)

    return 0;
}
