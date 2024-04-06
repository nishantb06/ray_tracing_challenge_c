# ifndef SCENE_H
# define SCENE_H

#include "tuple.h"
#include "matrix.h"
#include "ray.h"
#include "canvas.h"
#include "transformation.h"
#include "light.h"

typedef struct {
    Light* lights;
    int num_lights;
    Sphere* objects;
    int num_objects;
} World;

World* World_()
{
    World* world = (World*)malloc(sizeof(World));
    world->lights = NULL;
    world->num_lights = 0;
    world->objects = NULL;
    world->num_objects = 0;
    return world;
}

World* DefaultWorld()
{
    World* world = World_();
    world->num_lights = 1;
    world->lights = (Light*)malloc(world->num_lights * sizeof(Light));
    world->lights[0] = *Light_(Point(-10, 10, -10), Color_(1, 1, 1));

    world->num_objects = 2;
    world->objects = (Sphere*)malloc(world->num_objects * sizeof(Sphere));
    world->objects[0] = Sphere_(1,1);
    world->objects[0].material->color = Color_(0.8, 1.0, 0.6);
    world->objects[0].material->diffuse = 0.7;
    world->objects[0].material->specular = 0.2;

    world->objects[1] = Sphere_(1,2);
    world->objects[1].transform = Scaling(0.5, 0.5, 0.5);
    return world;
}

// Comparator function for qsort
int compareIntersections(const void *a, const void *b)
{
    Intersection *intersectionA = (Intersection *)a;
    Intersection *intersectionB = (Intersection *)b;
    return (intersectionA->t > intersectionB->t) - (intersectionA->t < intersectionB->t);
}

// The intersect_world function should iterate over all of the objects that have been 
// added to the world, intersecting each of them with the ray, and aggregating the 
// intersections into a single collection. Note that for the test to pass intersect_world 
// must return the intersections in sorted order
Intersections *IntersectWorld2(World *world, Ray *ray)
{   
    printf("Intersecting world\n");
    int max_intersections = world->num_objects * 2;
    Intersection* solutions = (Intersection*)malloc(sizeof(Intersection) * max_intersections);
    Intersections *allIntersections = Intersections__(max_intersections, solutions); // Step 1

    for (int i = 0; i < world->num_objects; i++)
    { // Step 2
        printf("Intersecting object %d\n", i);
        Sphere currentSphere = world->objects[i];
        Intersections *sphereIntersections = Intersect(currentSphere, *ray); // Step 3
        printf("Found %d intersections\n", sphereIntersections->count);
        for (int j = 0; j < sphereIntersections->count; j++)
        { // Step 4
            // printf("Adding intersection %d\n", j);
            allIntersections->solutions[i+j] = sphereIntersections->solutions[j];
        }
        free(sphereIntersections); // Free the temporary intersections structure
    }

    // Step 5: Sort the intersections
    printf("Sorting intersections\n");
    qsort(allIntersections->solutions, allIntersections->count, sizeof(Intersection), compareIntersections);

    return allIntersections; // Step 6
}

void sortIntersections(Intersections* intersections)
{
    qsort(intersections->solutions, intersections->count, sizeof(Intersection), compareIntersections);
}

Intersections* IntersectWorld(World* world, Ray* ray)
{   
    Intersections* result;
    Intersection* allIntersections = (Intersection *)malloc(sizeof(Intersection) * (world->num_objects * 2));
    int count = 0;
    for (int i = 0; i < world->num_objects; i++)
    {
        Intersections *intersections = Intersect(world->objects[i], *ray);
        // printf("Intersecting object %d\n", i);
        for (int j = 0; j < intersections->count; j++)
        {
            // printf("Adding intersection %d\n", j);
            allIntersections[count] = intersections->solutions[j];
            count++;
        }
        // free(intersections);
    }

    result = Intersections__(count, allIntersections);
    sortIntersections(result);
    return result;
}

typedef struct {
    int t;
    Sphere object;
    Tuple point;
    Tuple eyev;
    Tuple normalv;
    bool inside;
} Computation;

Computation* Computation_(int t, Sphere object, Tuple point, Tuple eyev, Tuple normalv, bool inside)
{
    Computation* comp = (Computation*)malloc(sizeof(Computation));
    comp->t = t;
    comp->object = object;
    comp->point = point;
    comp->eyev = eyev;
    comp->normalv = normalv;
    comp->inside = inside;
    return comp;
}

Computation *PrepareComputations(Intersection *intersection, Ray *ray)
{
    Sphere object = intersection->object;
    Tuple point = Position(*ray, intersection->t);
    Tuple eyev = ray->direction;
    Negate(&eyev);
    Tuple* normalv = NormalAt(object, point);
    bool inside = false;
    if (DotProduct(normalv, &eyev) < 0)
    {
        Negate(normalv);
        inside = true;
    }
    return Computation_(intersection->t, object, point, eyev, *normalv, inside);
}

Color ShadeHit(World *world, Computation *computation)
{   
    Color final_color = Color_(0, 0, 0);
    Color color = Color_(0, 0, 0);
    for (int i = 0; i < world->num_lights; i++)
    {
        Light light = world->lights[i];
        color = Lighting(computation->object.material, &light, computation->point, computation->eyev, computation->normalv );
        final_color = AddColor(final_color, color);
    }
    return final_color;
}

Color ColorAt(World *world, Ray *ray)
{
    Intersections *intersections = IntersectWorld(world, ray);
    if (intersections->count == 0)
    {
        return Color_(0, 0, 0);
    }
    Intersection* hit = Hit(intersections);
    if (hit == NULL || hit->t == -1 || hit->t == 0 )
    {
        return Color_(0, 0, 0);
    }
    Computation *computation = PrepareComputations(hit, ray);
    return ShadeHit(world, computation);
}


# endif // SCENE_H
