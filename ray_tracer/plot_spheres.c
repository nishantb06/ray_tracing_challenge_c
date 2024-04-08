// plot chapter 8 spheres

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "src/tuple.h"
#include "src/matrix.h"
#include "src/transformation.h"
#include "src/ray.h"
#include "src/light.h"
#include "src/canvas.h"
#include "src/scene.h"

// “This was constructed from six spheres, arranged as follows:”
int main()
{
    // floor is an extremely flattened sphere with matte texture
    Sphere floor = Sphere_(1, 1);
    SetTransform(&floor, Scaling(10, 0.01, 10));
    SetMaterial(&floor, Material_(Color_(1, 0.9, 0.9), 0.1, 0.9, 0.9, 200.0));

    // wall on the left is a sphere with matte texture
    Sphere left_wall = Sphere_(1, 2);
    SetTransform(&left_wall, MultiplyMatrices(Translation(0, 0, 5), MultiplyMatrices(RotationY(-M_PI/4), MultiplyMatrices(RotationX(M_PI/2), Scaling(10, 0.01, 10)))));
    SetMaterial(&left_wall, floor.material);

    // wall on the right is a sphere with matte texture
    Sphere right_wall = Sphere_(1, 3);
    SetTransform(&right_wall, MultiplyMatrices(Translation(0, 0, 5), MultiplyMatrices(RotationY(M_PI/4), MultiplyMatrices(RotationX(M_PI/2), Scaling(10, 0.01, 10)))));
    SetMaterial(&right_wall, floor.material);

    // middle is a sphere with matte texture
    Sphere middle = Sphere_(1, 4);
    SetTransform(&middle, Translation(-0.5, 1, 0.5));
    SetMaterial(&middle, Material_(Color_(0.1, 1, 0.5), 0.1, 0.7, 0.9, 200.0));

    // right is a sphere with matte texture
    Sphere right = Sphere_(1, 5);
    SetTransform(&right, MultiplyMatrices(Translation(1.5, 0.5, -0.5), Scaling(0.5, 0.5, 0.5)));
    SetMaterial(&right, Material_(Color_(0.5, 1, 0.1), 0.1, 0.7, 0.9, 200.0));

    // left is a sphere with matte texture
    Sphere left = Sphere_(1, 6);
    SetTransform(&left, MultiplyMatrices(Translation(-1.5, 0.33, -0.75), Scaling(0.33, 0.33, 0.33)));
    SetMaterial(&left, Material_(Color_(1, 0.8, 0.1), 0.1, 0.7, 0.9, 200.0));

    // light source
    Light* light = Light_(Point(-10, 10, -10), Color_(1, 1, 1));

    // world
    World* w = World_();
    AddObject(w, floor);
    AddObject(w, left_wall);
    AddObject(w, right_wall);
    AddObject(w, middle);
    AddObject(w, right);
    AddObject(w, left);
    w->num_lights = 1;
    w->lights = light;
    
    // camera
    Camera* camera = Camera_(1000, 500, M_PI/3);
    camera->transform = ViewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0));

    // render
    Canvas image = Render(camera, w);
    char *ppm = CanvasToPPM2(&image);
    if (ppm == NULL)
    {
        printf("Error: CanvasToPPM returned NULL\n");
        return 1;
    }
    const char *filename = "plot_spheres.ppm";
    PPMToFile(ppm, filename);
    printf("PPM string written to file: %s\n", filename);
    free(ppm);

    return 0;
}