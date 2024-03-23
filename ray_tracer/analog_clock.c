#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tuple.h"
#include "canvas.h"
#include "transformation.h"

// create an analog clock with the transformation functions

int main()
{
    Canvas c = Canvas_(800, 800);
    Color white = Color_(1, 1, 1);
    Color red = Color_(1, 0, 0);

    Tuple origin = Point(0, 0, 0);
    int radius = 300;
    int hours = 12;
    // translate the origin to the center of the canvas
    Matrix *translate = Translation(400, 400, 0);
    Tuple *center = MultiplyMatrixByTuple(translate, &origin);
    int x = (int)center->x;
    int y = c.height - (int)center->y;
    printf("x: %d, y: %d\n", x, y);
    WritePixel(&c, x, y, white);
    Matrix* translate2 = Translation(0, 300, 0);
    Tuple *twelve = MultiplyMatrixByTuple(translate2, &origin);
    Tuple *twelve2 = MultiplyMatrixByTuple(translate, twelve);
    // draw the twelve
    x = (int)twelve2->x; //400
    y = c.height - (int)twelve2->y; //100
    printf("x: %d, y: %d\n", x, y);
    WritePixel(&c, x, y, white);
    // get all the other points by rotating the point 30 degrees along the z axis
    for (int i = 1; i < hours; i++)
    {
        Matrix *rotate = RotationZ(-i * M_PI/6);
        Tuple *point = MultiplyMatrixByTuple(rotate, twelve);
        point = MultiplyMatrixByTuple(translate, point);
        int x = (int)point->x;
        int y = c.height - (int)point->y;
        printf("x: %d, y: %d\n", x, y);
        WritePixel(&c, x, y, white);
    }
    // translate twelve 400,-400,0
    // draw the twelve
    // Matrix *translate2 = Translation(400, -400, 0);
    // Tuple *twelve2 = MultiplyMatrixByTuple(translate2, twelve);
    // int x = (int)twelve2->x;
    // int y = c.height + (int)twelve2->y;
    // WritePixel(&c, x, y, white);

    char *ppm = CanvasToPPM2(&c);
    if (ppm == NULL)
    {
        printf("Error: CanvasToPPM returned NULL\n");
        return 1;
    }
    const char *filename = "analog_clock.ppm";
    PPMToFile(ppm, filename);
    printf("PPM string written to file: %s\n", filename);
    free(ppm);

    return 0;
}