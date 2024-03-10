#include <stdio.h>
#include <stdlib.h> // Add missing import for 'stdlib.h'
#include "canvas.h"

int main()
{
    // Example usage
    // const char *ppm = "P3\n5 3\n255\n255 0 0 0 255 0 0 0 255 0 0 0 255 0 0 0 255 0 0 0 255 0 0 0 255\n";
    Canvas c = Canvas_(500, 300); // Modify function name to 'Canvas' instead of 'Canvas_'
    char *ppm = CanvasToPPM(&c);
    if (ppm == NULL)
    {
        printf("Error: CanvasToPPM returned NULL\n");
        return 1;
    }
    const char *filename = "output2.ppm";
    PPMToFile(ppm, filename);
    printf("PPM string written to file: %s\n", filename);
    free(ppm); // Add deallocation for 'ppm'
    return 0;

}