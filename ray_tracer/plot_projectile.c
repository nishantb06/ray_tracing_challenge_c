#include <stdio.h>
#include <stdlib.h> // Add missing import for 'stdlib.h'
#include "canvas.h"
#include "projectile.h"
#include "tuple.h"

int main(){
    
    Tuple position = Point(0, 1, 0);
    Tuple velocity = Vector(1, 1.8, 0);
    Normalize(&velocity);
    ScalerMultiply(&velocity, 11.25);

    Tuple gravity = Vector(0, -0.1, 0);
    Tuple wind = Vector(-0.01, 0, 0);

    Environment e = Environment_(gravity, wind);
    Projectile p = Projectile_(position, velocity);

    // run the tick function untill the y position is less than 0
    // tick(&e, &p);
    Canvas c = Canvas_(900, 550);
    Color red = Color_(1, 0, 0);
    while(p.position.y > 0){
        tick(&e, &p);
        int x = (int)p.position.x;
        int y = c.height - (int)p.position.y;
        // make sure the x and y are within the canvas
        if(x >= 0 && x < c.width && y >= 0 && y < c.height)
        {
            WritePixel(&c, x, y, red);
        }
    }

    // write the canvas to a file
    char *ppm = CanvasToPPM2(&c);
    if (ppm == NULL)
    {
        printf("Error: CanvasToPPM returned NULL\n");
        return 1;
    }
    const char *filename = "projectile.ppm";
    PPMToFile(ppm, filename);
    printf("PPM string written to file: %s\n", filename);
    free(ppm); // Add deallocation for 'ppm'

    return 0;
}