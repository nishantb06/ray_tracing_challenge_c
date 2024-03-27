#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "tuple.h"
#include "matrix.h"
#include "transformation.h"
#include "ray.h"

void test_ray()
{
    Tuple origin = Point(1, 2, 3);
    Tuple direction = Vector(4, 5, 6);
    Ray r = Ray_(origin, direction);
    assert(equal(r.origin, origin));
    assert(equal(r.direction, direction));
    printf("Test ray passed\n");

    Ray r2 = Ray_(Point(2, 3, 4), Vector(1, 0, 0));
    Tuple p = Position(r2, 0);
    Tuple expected = Point(2, 3, 4);
    assert(equal(p, expected));
    p = Position(r2, 1);
    expected = Point(3, 3, 4);
    assert(equal(p, expected));
    p = Position(r2, -1);
    expected = Point(1, 3, 4);
    assert(equal(p, expected));
    p = Position(r2, 2.5);
    expected = Point(4.5, 3, 4);
    printf("Test position passed\n");
}

void test_intersecting_ray_with_sphere()
{
    Ray r1 = Ray_(Point(0,0,-5),Vector(0,0,1));
    Sphere s1 = Sphere_(1.0 , 1);
    Intersections* i1 = Intersect(s1, r1);
    assert(i1->count == 2);
    assert(i1->solutions[0].t==4);
    assert(i1->solutions[1].t==6);
    printf("Test intersecting ray with spehere at 2 points passed\n");

    Ray r2 = Ray_(Point(0, 1, -5), Vector(0, 0, 1));
    Intersections* i2 = Intersect(s1, r2);
    assert(i2->count==2);
    assert(i2->solutions[0].t == 5);
    assert(i2->solutions[1].t == 5);
    printf("Test intersecting ray with spehere at 1 points passed\n");

    Ray r3 = Ray_(Point(0, 2, -5), Vector(0, 0, 1));
    Intersections* i3 = Intersect(s1, r3);
    assert(i3->count == 0);
    printf("Test intersecting ray with spehere at 0 points passed\n");

    Ray r4 = Ray_(Point(0, 0, 0), Vector(0, 0, 1));
    Intersections* i4 = Intersect(s1, r4);
    assert(i4->count == 2);
    assert(i4->solutions[0].t == -1);
    assert(i4->solutions[1].t == 1);
    printf("Test intersecting ray with spehere when ray originates inside passed\n");

    Ray r5 = Ray_(Point(0, 0, 5), Vector(0, 0, 1));
    Intersections* i5 = Intersect(s1, r5);
    assert(i5->count == 2);
    assert(i5->solutions[0].t == -6);
    assert(i5->solutions[1].t == -4);
    printf("Test intersecting ray with spehere when ray originates inside passed\n");

}

void test_intersection()
{
    Sphere s = Sphere_(1, 1);
    Intersection* i0 = Intersection_(3.5, s);
    assert(i0->t == 3.5);
    assert(i0->object.id == 1);
    free(i0);
    // delete i from memory
    printf("Test intersection passed\n");

    Intersection* i1 = Intersection_(1, s);
    Intersection* i2 = Intersection_(2, s);
    Intersection* i = (Intersection*)malloc(sizeof(Intersection)*2);
    i[0] = *i1;
    i[1] = *i2;
    Intersections* xs = Intersections__(2, i);
    assert(xs->count == 2);
    assert(xs->solutions[0].t == 1);
    assert(xs->solutions[1].t == 2);
    free(i1);
    free(i2);
    free(i);
    printf("Test intersections 2 passed\n");

}


int main ()
{
    test_ray();
    test_intersecting_ray_with_sphere();
    test_intersection();
    return 0;
}