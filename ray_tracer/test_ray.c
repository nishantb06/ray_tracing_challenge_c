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

void test_intersections_and_hit()
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

    Intersection* i3 = Intersection_(1, s);
    Intersection* i4 = Intersection_(2, s);
    Intersection* i5 = Intersection_(-1, s);
    Intersection* i6 = Intersection_(-2, s);
    Intersection* i7 = Intersection_(5, s);
    Intersection* i8 = Intersection_(7, s);
    Intersection* i9 = Intersection_(-3, s);
    Intersection* i10 = Intersection_(2, s);

    Intersection* iarr1 = (Intersection*)malloc(sizeof(Intersection)*2);
    iarr1[0] = *i3;
    iarr1[1] = *i4;
    Intersections* xs1 = Intersections__(2, iarr1);
    Intersection* hit1 = Hit(xs1);
    assert(hit1->t == 1);
    printf("Test hit 1 passed\n");

    Intersection* iarr2 = (Intersection*)malloc(sizeof(Intersection)*2);
    iarr2[0] = *i5;
    iarr2[1] = *i3;
    Intersections* xs2 = Intersections__(2, iarr2);
    Intersection* hit2 = Hit(xs2);
    assert(hit2->t == 1);
    printf("Test hit 2 passed\n");

    Intersection* iarr3 = (Intersection*)malloc(sizeof(Intersection)*2);
    iarr3[0] = *i5;
    iarr3[1] = *i6;
    Intersections* xs3 = Intersections__(2, iarr3);
    Intersection* hit3 = Hit(xs3);
    assert(hit3 == NULL);
    printf("Test hit 3 passed\n");

    Intersection* iarr4 = (Intersection*)malloc(sizeof(Intersection)*4);
    iarr4[0] = *i7;
    iarr4[1] = *i8;
    iarr4[2] = *i9;
    iarr4[3] = *i10;
    Intersections* xs4 = Intersections__(4, iarr4);
    Intersection* hit4 = Hit(xs4);
    assert(hit4->t == 2);
    printf("Test hit 4 passed\n");

}

void test_transforms()
{
    // translating a ray
    Ray r = Ray_(Point(1, 2, 3), Vector(0, 1, 0));
    Matrix* translate = Translation(3, 4, 5);
    Ray r2 = Transform(r, translate);
    assert(equal(r2.origin, Point(4, 6, 8)));
    assert(equal(r2.direction, Vector(0, 1, 0)));
    printf("Test translating a ray passed\n");

    // scaling a ray
    Ray r3 = Ray_(Point(1, 2, 3), Vector(0, 1, 0));
    Matrix* scale = Scaling(2, 3, 4);
    Ray r4 = Transform(r3, scale);
    assert(equal(r4.origin, Point(2, 6, 12)));
    assert(equal(r4.direction, Vector(0, 3, 0)));
    printf("Test scaling a ray passed\n");

    // a spheres default transformation
    Sphere s = Sphere_(1, 1);
    Matrix* m = s.transform;
    assert(CompareMatrices(m, IdentityMatrix(4)));
    printf("Test sphere default transformation passed\n");

    // changing a spheres transformation
    Matrix* t = Translation(2, 3, 4);
    SetTransform(&s, t);
    assert(CompareMatrices(s.transform, t));
    printf("Test changing a spheres transformation passed\n");

    // intersecting a scaled sphere with a ray
    Ray r5 = Ray_(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s2 = Sphere_(1, 1);
    SetTransform(&s2, Scaling(2, 2, 2));
    Intersections* i = Intersect(s2, r5);
    assert(i->count == 2);
    printf("Test intersecting a scaled sphere with a ray passed\n");
}



int main ()
{
    test_ray();
    test_intersecting_ray_with_sphere();
    test_intersections_and_hit();
    test_transforms();
    return 0;
}