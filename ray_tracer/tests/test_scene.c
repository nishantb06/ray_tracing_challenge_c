#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "../src/tuple.h"
#include "../src/matrix.h"
#include "../src/transformation.h"
#include "../src/ray.h"
#include "../src/light.h"
#include "../src/canvas.h"
#include "../src/scene.h"

void test_world()
{
    World* w = World_();
    assert(w->num_lights == 0);
    assert(w->num_objects == 0);
    printf("Test world1 passed\n");

    // testing default world
    w = DefaultWorld();
    assert(w->num_lights == 1);
    assert(w->num_objects == 2);
    Sphere s1 = w->objects[0];
    Sphere s2 = w->objects[1];
    Sphere s3 = Sphere_(1, 1);
    Sphere s4 = Sphere_(1, 2);
    SetTransform(&s4, Scaling(0.5, 0.5, 0.5));
    assert(s1.id == s3.id);
    assert(s1.radius == s3.radius);
    assert(s2.id == s4.id);
    assert(s2.radius == s4.radius);
    printf("Testing default world passed\n");

    // intersect a world with a ray
    Ray r = Ray_(Point(0, 0, -5), Vector(0, 0, 1));
    Intersections* xs = IntersectWorld(w, &r);
    assert(xs->count == 4);
    assert(xs->solutions[0].t == 4);
    assert(xs->solutions[1].t == 4.5);
    assert(xs->solutions[2].t == 5.5);
    assert(xs->solutions[3].t == 6);
    printf("Test intersect world passed\n");

    // testing precomputing the state of an intersection
    r = Ray_(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere_(1, 1);
    Intersection* i = Intersection_(4, s);
    Computation* comps = PrepareComputations(i, &r);
    assert(comps->t == i->t);
    assert(comps->object.id == i->object.id);
    assert(equal(comps->point, Point(0, 0, -1)));
    assert(equal(comps->eyev, Vector(0, 0, -1)));
    assert(equal(comps->normalv, Vector(0, 0, -1)));
    printf("Test prepare computations passed\n");

    // hit when intersection occurs on the outside
    r = Ray_(Point(0, 0, -5), Vector(0, 0, 1));
    i = Intersection_(4, s);
    comps = PrepareComputations(i, &r);
    assert(comps->inside == false);
    printf("Test hit when intersection occurs on the outside passed\n");

    // hit when intersection occurs on the inside
    r = Ray_(Point(0, 0, 0), Vector(0, 0, 1));
    i = Intersection_(1, s);
    comps = PrepareComputations(i, &r);
    assert(equal(comps->point, Point(0, 0, 1)));
    assert(equal(comps->eyev, Vector(0, 0, -1)));
    assert(comps->inside == true);
    assert(equal(comps->normalv, Vector(0, 0, -1)));
    printf("Test hit when intersection occurs on the inside passed\n");
    
}

int main()
{
    printf("=======Running tests for scene, chapter 8======\n");
    test_world();
    return 0;
}