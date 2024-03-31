# ifndef RAY_H
# define RAY_H
#include <math.h>
# include "tuple.h"
# include "matrix.h"
# include "transformation.h"

typedef struct {
    Tuple origin;
    Tuple direction;
} Ray;

Ray Ray_(Tuple origin, Tuple direction)
{
    Ray ray;
    ray.origin = origin;
    ray.direction = direction;
    return ray;
}

Tuple Position(Ray ray, double t)
{   
    ScalerMultiply(&ray.direction, t);
    return Add(ray.origin, ray.direction);
}

typedef struct{
    float radius;
    Tuple center;
    float id;
    Matrix *transform;
} Sphere;

Sphere Sphere_(float radius, float id)
{
    Sphere s;
    s.center = Point(0, 0, 0);
    s.radius = radius;
    s.id = id;
    s.transform = IdentityMatrix(4);
    return s;
}

Tuple* NormalAt(Sphere s, Tuple world_point)
{
    Tuple *object_point = MultiplyMatrixByTuple(Inverse(s.transform), &world_point);
    Tuple object_normal = Subtract(*object_point, Point(0, 0, 0));
    Tuple *world_normal = MultiplyMatrixByTuple(TransposeMatrix(Inverse(s.transform)), &object_normal);
    world_normal->w = 0;
    Normalize(world_normal);
    return world_normal;
}

Tuple Reflect(Tuple* in, Tuple* normal)
{
    ScalerMultiply(normal, 2 * DotProduct(in, normal));
    Tuple result = Subtract(*in, *normal);
    return result;
}

void SetTransform(Sphere *s, Matrix *m)
{
    s->transform = m;
}

float *Discriminant(Ray r, Sphere s)
{
    float d;
    float a = DotProduct(&r.direction, &r.direction);
    Tuple sphere_to_ray = Subtract(r.origin, s.center);
    float b = 2 * (DotProduct(&r.direction, &sphere_to_ray));
    float c = DotProduct(&sphere_to_ray, &sphere_to_ray) - 1;
    float *values = (float *)malloc(sizeof(float) * 4);
    values[0] = a;
    values[1] = b;
    values[2] = c;
    d = b * b - 4 * a * c;
    values[3] = d;

    return values;
}

typedef struct
{
    float t;
    Sphere object;
} Intersection;

typedef struct
{
    Intersection* solutions;
    int count;
} Intersections;


Intersection* Intersection_(float t, Sphere object)
{
    Intersection* i = (Intersection*)malloc(sizeof(Intersection));
    i->t = t;
    i->object = object;
    return i;
}

Intersections* Intersections_()
{
    Intersections* i;
    i->count = -1;
    i->solutions = NULL;
    return i;
}

Intersections* Intersections__(int count, Intersection *i)
{
    // count represents the number of intersections
    // i is an array of intersections of size count
    Intersections* intersections;
    intersections->count = count;
    intersections->solutions = (Intersection*)malloc(sizeof(Intersection)*count);
    intersections->solutions = i;
    return intersections;
}

Ray Transform(Ray r, Matrix *m)
{
    Ray ray;
    ray.origin = *MultiplyMatrixByTuple(m, &r.origin);
    ray.direction = *MultiplyMatrixByTuple(m, &r.direction);
    return ray;
}
void PrintRay(Ray r)
{
    printf("Origin: ");
    PrintTuple(r.origin);
    printf("Direction: ");
    PrintTuple(r.direction);
}
Intersections* Intersect(Sphere s, Ray r)
{
    // transform the ray
    // inverse of the transformation matrix
    Matrix* m = Inverse(s.transform);
    Ray r2 = Transform(r, m);
    Intersections* i = Intersections_();
    float* values = Discriminant(r2,s);
    float d = values[3];
    float a = values[0];
    float b = values[1];
    float c = values[2];
    // printf("a: %f, b: %f, c: %f, d: %f\n", a, b, c, d);
    if(d<0){
        i->count = 0;
        return i;
    }
    float t1 = (-b + sqrt(d)) / (2 * a);
    float t2 = (-b - sqrt(d)) / (2 * a);
    // printf("t1: %f, t2: %f\n", t1, t2);
    if (t1 >= t2)
    {
        i->count = 2;
        Intersection* i1 = Intersection_(t2, s);
        Intersection* i2 = Intersection_(t1, s);
        Intersection* i = (Intersection*)malloc(sizeof(Intersection)*2);
        i[0] = *i1;
        i[1] = *i2;
        return Intersections__(2, i);
    }
    else{
        i->count = 2;
        Intersection* i1 = Intersection_(t1, s);
        Intersection* i2 = Intersection_(t2, s);
        Intersection* i = (Intersection*)malloc(sizeof(Intersection)*2);
        i[0] = *i1;
        i[1] = *i2;
        return Intersections__(2, i);
    }
    return i; 
}

Intersection* Hit(Intersections* i)
{
    if(i->count == 0)
    {
        return NULL;
    }
    Intersection* hit = (Intersection*)malloc(sizeof(Intersection));
    float min = 1000000;
    for(int j=0; j<i->count; j++)
    {
        if(i->solutions[j].t < min && i->solutions[j].t > 0)
        {
            min = i->solutions[j].t;
            *hit = i->solutions[j];
        }
        else
        {
            continue;
        }
    }
    if (min == 1000000 || min < 0)
    {
        return NULL;
    }
    return hit;
}




# endif // RAY_H