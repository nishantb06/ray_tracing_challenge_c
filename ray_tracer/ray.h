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
} Sphere;

Sphere Sphere_(float radius, float id)
{
    Sphere s;
    s.center = Point(0, 0, 0);
    s.radius = radius;
    s.id = id;
    return s;
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

// Intersections Intersections_()
// {
//     float *solutions = (float *)malloc(sizeof(float) * 2);
//     Intersections i;
//     i.solutions = solutions;
//     i.count = -1;
//     return i;
// }

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


Intersections* Intersect(Sphere s, Ray r)
{
    Intersections* i = Intersections_();
    float* values = Discriminant(r,s);
    float d = values[3];
    float a = values[0];
    float b = values[1];
    float c = values[2];
    if(d<0){
        i->count = 0;
        return i;
    }
    float t1 = (-b + sqrt(d)) / (2 * a);
    float t2 = (-b - sqrt(d)) / (2 * a);
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