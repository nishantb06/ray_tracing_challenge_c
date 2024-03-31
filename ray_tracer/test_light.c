#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "tuple.h"
#include "matrix.h"
#include "transformation.h"
#include "ray.h"
#include "light.h"
#include "canvas.h"

void test_light()
{
    Tuple position = Point(0, 0, 0);
    Color intensity = Color_(1, 1, 1);
    Light* l = Light_(position, intensity);
    assert(equal(l->position, position));
    assert(ColorIsEqual(l->intensity, intensity));
    printf("Test light passed\n");

    Material* m = DefaultMaterial();
    // eye between the light and the surface
    Tuple eye = Vector(0, 0, -1);
    Tuple normal = Vector(0, 0, -1);
    Tuple light_position = Point(0, 0, -10);
    Color result = Lighting(m, l, position, eye, normal);
    assert(ColorIsEqual(result, Color_(1.9, 1.9, 1.9)));

    // eye between light and surface, eye offset 45 degrees
    eye = Vector(0, sqrt(2)/2, -sqrt(2)/2);
    normal = Vector(0, 0, -1);
    result = Lighting(m, l, position, eye, normal);
    assert(ColorIsEqual(result, Color_(1.0, 1.0, 1.0)));

    // light between eye and surface, eye offset 45 degrees
    eye = Vector(0, 0, -1);
    normal = Vector(0, 0, -1);
    result = Lighting(m, l, position, eye, normal);
    assert(ColorIsEqual(result, Color_(1.0, 1.0, 1.0)));

    // light between eye and surface, eye offset 45 degrees, light offset 45 degrees
    eye = Vector(0, sqrt(2)/2, -sqrt(2)/2);
    normal = Vector(0, 0, -1);
    result = Lighting(m, l, position, eye, normal);
    assert(ColorIsEqual(result, Color_(0.7364, 0.7364, 0.7364)));

    // eye opposite surface, light offset 45 degrees
    eye = Vector(0, 0, -1);
    normal = Vector(0, 0, -1);
    result = Lighting(m, l, position, eye, normal);
    assert(ColorIsEqual(result, Color_(0.1, 0.1, 0.1)));

    // eye in the path of the reflection vector
    eye = Vector(0, -sqrt(2)/2, -sqrt(2)/2);
    normal = Vector(0, 0, -1);
    result = Lighting(m, l, position, eye, normal);
    assert(ColorIsEqual(result, Color_(1.6364, 1.6364, 1.6364)));
    
    printf("Test lighting passed\n");
}

void test_material()
{   
    Color c = Color_(1, 1, 1);
    Material* m = Material_(c, 0.1, 0.9, 0.9, 200.0);
    assert(fabs(m->ambient - 0.1) < EPSILON);
    assert(fabs(m->diffuse - 0.9) < EPSILON);
    assert(fabs(m->specular - 0.9) < EPSILON);
    assert(fabs(m->shininess - 200.0) < EPSILON);
    assert(ColorIsEqual(m->color, Color_(1, 1, 1)));
    printf("Test material passed\n");

    // sphere has a default material
    Sphere s1 = Sphere_(1.0, 1);
    Material* m2 = s1.material;
    assert(fabs(m2->ambient - 0.1) < EPSILON);
    assert(fabs(m2->diffuse - 0.9) < EPSILON);
    assert(fabs(m2->specular - 0.9) < EPSILON);
    assert(fabs(m2->shininess - 200.0) < EPSILON);
    assert(ColorIsEqual(m2->color, Color_(1, 1, 1)));
    printf("Test material 2 passed\n");

    // sphere may be assigned a material
    Material* m3 = Material_(Color_(1, 0, 0), 1, 0.9, 0.9, 200.0);
    SetMaterial(&s1, m3);
    Material* m4 = s1.material;
    assert(fabs(m4->ambient - 1) < EPSILON);
    assert(fabs(m4->diffuse - 0.9) < EPSILON);
    assert(fabs(m4->specular - 0.9) < EPSILON);
    assert(fabs(m4->shininess - 200.0) < EPSILON);
    assert(ColorIsEqual(m4->color, Color_(1, 0, 0)));
    printf("Test material 3 passed\n");
}

int main()
{
    test_light();
    test_material();
    return 0;
}