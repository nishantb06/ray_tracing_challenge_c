#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tuple.h"
#include "matrix.h"
#include "transformation.h"
#include "ray.h"
#include "canvas.h"

int main()
{
    Canvas c = Canvas_(1000, 1000);
    Color red = Color_(1, 0, 0);
    Sphere s = Sphere_(1, 1);
    // Apply a shearing and scaling transformation to the sphere
    Matrix *shear = Shearing(1, 0, 0, 0, 0, 0);
    Matrix *scale = Scaling(0.5, 1, 1);
    Matrix *transform = MultiplyMatrices(shear, scale);
    SetTransform(&s, transform);

    Tuple ray_origin = Point(0, 0, -5);
    float wall_z = 10;
    float wall_size = 10;
    float pixel_size = wall_size / c.width;
    float half = wall_size / 2;
    
    for (int y = 0; y < c.height; y++)
    {
        float world_y = half - pixel_size * y;
        for (int x = 0; x < c.width; x++)
        {
            float world_x = -half + pixel_size * x;
            Tuple position = Point(world_x, world_y, wall_z);
            Tuple direction = Subtract(position, ray_origin);
            Normalize(&direction);
            Ray r = Ray_(ray_origin, direction);
            Intersections *intersections = Intersect(s, r);
            if (Hit(intersections) != NULL)
            {
                WritePixel(&c, x, y, red);
            }
        }
    }
    char *ppm = CanvasToPPM2(&c);
    if (ppm == NULL)
    {
        printf("Error: CanvasToPPM returned NULL\n");
        return 1;
    }
    const char *filename = "circle.ppm";
    PPMToFile(ppm, filename);
    printf("PPM string written to file: %s\n", filename);
    free(ppm);


    return 0;
}