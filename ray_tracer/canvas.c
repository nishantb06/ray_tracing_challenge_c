#include <stdio.h>
#include <stdlib.h> // Add missing import for 'stdlib.h'
#include "canvas.h"

char* CanvasToPPM2(Canvas *c) // Change function name to 'CanvasToPPM2' instead of 'CanvasToPPM'
{
    char *ppm = (char *)malloc(1000000); // Increase size of 'ppm' to 1000000
    if (ppm == NULL)
    {
        return NULL;
    }
    int index = 0;
    
    printf("Canvas width: %d\n", c->width);
    printf("Canvas height: %d\n", c->height);

    index += sprintf(ppm, "P3\n%d %d\n255\n", c->width, c->height);
    for (int i = 0; i < c->height; i++)
    {
        for (int j = 0; j < c->width; j++)
        {
            Color pixel = c->pixels[j][i];
            index += sprintf(ppm + index, "%d %d %d ", clamp((int)(pixel.red * 255)), clamp((int)(pixel.green * 255)), clamp((int)(pixel.blue * 255)));
        }
        index += sprintf(ppm + index, "\n");
    }
    return ppm;
}

int main()
{
    // Example usage
    // const char *ppm = "P3\n5 3\n255\n255 0 0 0 255 0 0 0 255 0 0 0 255 0 0 0 255 0 0 0 255 0 0 0 255\n";
    Canvas c = Canvas_(5, 3); // Modify function name to 'Canvas' instead of 'Canvas_'
    Color c1 = Color_(1.5f, 0.0f, 0.0f);
    Color c2 = Color_(0.0f, 0.5f, 0.0f);
    Color c3 = Color_(-0.5f, 0.0f, 1.0f);
    WritePixel(&c, 0, 0, c1);
    WritePixel(&c, 2, 1, c2);
    WritePixel(&c, 4, 2, c3);

    char *ppm = CanvasToPPM2(&c);
    if (ppm == NULL)
    {
        printf("Error: CanvasToPPM returned NULL\n");
        return 1;
    }
    const char *filename = "output2.ppm";
    PPMToFile(ppm, filename);
    printf("PPM string written to file: %s\n", filename);
    free(ppm); // Add deallocation for 'ppm'

    c = Canvas_(10, 2);
    for (int i = 0; i < c.width; i++)
    {
        for (int j = 0; j < c.height; j++)
        {
            Color color = Color_(1.0f, 0.8f, 0.6f);
            WritePixel(&c, i, j, color);
        }
    }
    ppm = CanvasToPPM2(&c);
    if (ppm == NULL)
    {
        printf("Error: CanvasToPPM returned NULL\n");
        return 1;
    }
    filename = "output3.ppm";
    PPMToFile(ppm, filename);
    printf("PPM string written to file: %s\n", filename);
    free(ppm); // Add deallocation for 'ppm'

    return 0;

}