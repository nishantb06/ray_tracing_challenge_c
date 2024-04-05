#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "src/tuple.h"
#include "src/matrix.h"
#include "src/transformation.h"
#include "src/ray.h"
#include "src/canvas.h"

int main()
{
    Canvas c = Canvas_(500, 500);
    Color red = Color_(1, 0, 0);
    Sphere s = Sphere_(1, 1);
    s.material = DefaultMaterial();
    s.material->color = Color_(1, 0.2, 0.2);
    // Apply a shearing and scaling transformation to the sphere
    Matrix *shear = Shearing(1, 0, 0, 0, 0, 0);
    Matrix *scale = Scaling(0.5, 1, 1);
    Matrix *transform = MultiplyMatrices(shear, scale);
    SetTransform(&s, transform);

    Tuple light_position = Point(-10, 10, -10);
    Color light_color = Color_(1, 1, 1);
    Light *light = Light_(light_position, light_color);

    Tuple ray_origin = Point(0, 0, -5); // Fixed ray origin
    float wall_z = 10;
    float wall_size = 7; // Adjusted for better framing
    float pixel_size = wall_size / c.width;
    float half = wall_size / 2;

    for (int y = 0; y < c.height; y++)
    {
        float world_y = half - pixel_size * y;
        for (int x = 0; x < c.width; x++)
        {
            float world_x = -half + pixel_size * x;
            Tuple position = Point(world_x, world_y, wall_z);
            Tuple direction = Subtract(position, ray_origin); // From ray origin to position
            Normalize(&direction);
            Ray r = Ray_(ray_origin, direction);
            Intersections *intersections = Intersect(s, r);
            if (Hit(intersections) != NULL)
            {
                Tuple point = Position(r, Hit(intersections)->t);
                Tuple* normal = NormalAt(s, point);                                    // Get the normal at the hit point
                Tuple eye = r.direction;
                Negate(&eye);                                      // Eye vector points back to the ray origin
                Color color = Lighting(s.material, light, point, eye, *normal); // False for inShadow
                WritePixel(&c, x, y, color);
            }
        }
    }
    char *ppm = CanvasToPPM2(&c);
    if (ppm == NULL)
    {
        printf("Error: CanvasToPPM returned NULL\n");
        return 1;
    }
    const char *filename = "sphere.ppm";
    PPMToFile(ppm, filename);
    printf("PPM string written to file: %s\n", filename);
    free(ppm);

    return 0;
}
