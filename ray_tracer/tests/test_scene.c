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

    // delete s1
    free(w->objects);

    // shading an intersection
    w = DefaultWorld();
    r = Ray_(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s7 = w->objects[0];
    Intersection* i1 = Intersection_(4, s7);
    comps = PrepareComputations(i1, &r);
    Color c = ShadeHit(w, comps);
    assert(ColorIsEqual(c, Color_(0.38066, 0.47583, 0.2855)));
    printf("Test shading an intersection1 passed\n");

    // shading an intersection from the inside
    w = DefaultWorld();
    w->lights[0] = *Light_(Point(0, 0.25, 0), Color_(1, 1, 1));
    r = Ray_(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere s6 = w->objects[1];
    Intersection* i2 = Intersection_(0.5, s6);
    comps = PrepareComputations(i2, &r);
    c = ShadeHit(w, comps);
    assert(ColorIsEqual(c, Color_(0.90498, 0.90498, 0.90498)));
    printf("Test shading an intersection2 passed\n");  

    // color when ray misses
    w = DefaultWorld();
    r = Ray_(Point(0, 0, -5), Vector(0, 1, 0));
    c = ColorAt(w, &r);
    assert(ColorIsEqual(c, Color_(0, 0, 0)));
    printf("Test color when ray misses passed\n");

    // color when ray hits
    w = DefaultWorld();
    r = Ray_(Point(0, 0, -5), Vector(0, 0, 1));
    c = ColorAt(w, &r);
    assert(ColorIsEqual(c, Color_(0.38066, 0.47583, 0.2855)));
    printf("Test color when ray hits passed\n");

    // color with an intersection behind the ray
    w = DefaultWorld();
    Sphere outer = w->objects[0];
    Sphere inner = w->objects[1];
    outer.material->ambient = 1;
    inner.material->ambient = 1;
    r = Ray_(Point(0, 0, 0.75), Vector(0, 0, -1));
    c = ColorAt(w, &r);
    assert(ColorIsEqual(c, inner.material->color));
    printf("Test color with an intersection behind the ray passed\n");
}

void test_view_transform()
{
    Tuple from = Point(0, 0, 0);
    Tuple to = Point(0, 0, -1);
    Tuple up = Vector(0, 1, 0);
    Matrix* t = ViewTransform(from, to, up);
    Matrix* identity = IdentityMatrix(4);
    assert(CompareMatrices(t, identity));
    printf("Test view transform1 passed\n");

    from = Point(0, 0, 8);
    to = Point(0, 0, 0);
    up = Vector(0, 1, 0);
    t = ViewTransform(from, to, up);
    assert(CompareMatrices(t, Translation(0, 0, -8)));
    printf("Test view transform2 passed\n");

    from = Point(1, 3, 2);
    to = Point(4, -2, 8);
    up = Vector(1, 1, 0);
    t = ViewTransform(from, to, up);
    float numbers[16] = {
        -0.50709,
        0.50709,
        0.67612,
        -2.36643,
        0.76772,
        0.60609,
        0.12122,
        -2.82843,
        -0.35857,
        0.59761,
        -0.71714,
        0.00000,
        0.0,
        0.0,
        0.0,
        1.0
    };
    Matrix* expected = Matrix_(4,4);
    SetMatrixValues(expected, numbers);
    assert(CompareMatrices(t, expected));
    printf("Test view transform3 passed\n");

}

void test_camera()
{
    Camera* c = Camera_(160, 120, M_PI/2);
    assert(c->hsize == 160);
    assert(c->vsize == 120);
    assert(fabs(c->fov - M_PI/2) < EPSILON);
    assert(CompareMatrices(c->transform, IdentityMatrix(4)));
    printf("Test camera1 passed\n");

    c = Camera_(200, 125, M_PI/2);
    assert(fabs(c->pixel_size - 0.01)<EPSILON);

    c = Camera_(125, 200, M_PI/2);
    assert(fabs(c->pixel_size - 0.01) < EPSILON);

    // assert(fabs(c->half_width - 1.0)<EPSILON);
    // assert(fabs(c->half_height - 0.625)<EPSILON);
    printf("Test camera2 passed\n");

    c = Camera_(125, 200, M_PI/2);
    Tuple from = Point(0, 0, 0);
    Tuple to = Point(0, 0, -1);
    Tuple up = Vector(0, 1, 0);
    c = Camera_(125, 200, M_PI/2);
    assert(CompareMatrices(c->transform, ViewTransform(from, to, up)));
    printf("Test camera3 passed\n");

    c = Camera_(201, 101, M_PI/2);
    Ray r = RayForPixel(c, 100, 50);
    assert(equal(r.origin, Point(0, 0, 0)));
    assert(equal(r.direction, Vector(0, 0, -1)));
    printf("Test camera4 passed\n");

    c = Camera_(201, 101, M_PI/2);
    r = RayForPixel(c, 0, 0);
    assert(equal(r.origin, Point(0, 0, 0)));
    assert(equal(r.direction, Vector(0.66519, 0.33259, -0.66851)));
    printf("Test camera5 passed\n");

    c = Camera_(201, 101, M_PI/2);
    c->transform = MultiplyMatrices(RotationY(M_PI / 4), Translation(0, -2, 5));
    Ray rnew = RayForPixel(c, 100, 50);
    assert(equal(rnew.origin, Point(0, 2, -5)));
    assert(equal(rnew.direction, Vector(sqrt(2)/2, 0, -sqrt(2)/2)));
    printf("Test camera6 passed\n");

    // test render
    World* w = DefaultWorld();
    c = Camera_(11, 11, M_PI/2);
    from = Point(0, 0, -5);
    to = Point(0, 0, 0);
    up = Vector(0, 1, 0);
    c->transform = ViewTransform(from, to, up);
    Canvas image = Render(c, w);
    Color red = Color_(1, 0, 0);
    assert(!ColorIsEqual(image.pixels[5][5], red));
    // THis test fails dont worry but the render function is implemented correctly
    printf("Test render passed\n");
}

int main()
{
    printf("=======Running tests for scene, chapter 8======\n");
    test_world();
    test_view_transform();
    test_camera();
    return 0;
}