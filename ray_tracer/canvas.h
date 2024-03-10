#ifndef CANVAS_H
#define CANVAS_H

#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "tuple.h"
#include "string.h"
#include <stdio.h>

typedef struct Color {
    float red;
    float green;
    float blue;
} Color;

// constructor for a color, just need to pass in the r, g, and b values
Color Color_(float r, float g, float b){
    Color c = {r, g, b};
    return c;
}

Color AddColor(Color a, Color b){
    return Color_(a.red + b.red, a.green + b.green, a.blue + b.blue);
}

Color SubtractColor(Color a, Color b){
    return Color_(a.red - b.red, a.green - b.green, a.blue - b.blue);
}

Color MultiplyColor(Color a, Color b){
    return Color_(a.red * b.red, a.green * b.green, a.blue * b.blue);
}

void ScalarMultiplyColor(Color* a, float b){
    a->red *= b;
    a->green *= b;
    a->blue *= b;
}

void ScalarDivideColor(Color *a, float b){
    a->red /= b;
    a->green /= b;
    a->blue /= b;
}

bool ColorIsEqual(Color a, Color b){
    return a.red == b.red && a.green == b.green && a.blue == b.blue;
}

typedef struct Canvas {
    int width;
    int height;
    Color **pixels;
} Canvas;

Canvas Canvas_(int width, int height){
    Canvas c;
    c.width = width;
    c.height = height;
    c.pixels = (Color **)malloc(sizeof(Color *) * width);

    for(int i = 0; i < width; i++){
        c.pixels[i] = (Color *)malloc(sizeof(Color) * height);
        for(int j = 0; j < height; j++){
            c.pixels[i][j] = Color_(0, 0, 0);
        }
    }

    return c;
}

void WritePixel(Canvas *c, int x, int y, Color color){
    c->pixels[x][y] = color;
}

// Function to clamp a value within a range
int clamp(int value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    if (value > max)
    {
        return max;
    }
    return value;
}

// Function to convert a Canvas to a PPM string
char *CanvasToPPM(Canvas *c)
{
    // Allocate memory for PPM string
    char *ppm = (char *)malloc(sizeof(char) * 100000); // Adjust size as needed

    // PPM header
    sprintf(ppm, "P3\n%d %d\n255\n", c->width, c->height);

    // Buffer for line of pixels
    char line[100] = "";
    int line_length = 0;

    // Iterate through pixels
    for (int i = 0; i < c->height; i++)
    {
        for (int j = 0; j < c->width; j++)
        {
            // Get color values and clamp to [0, 255]
            int red = clamp((int)(c->pixels[i][j].red * 255), 0, 255);
            int green = clamp((int)(c->pixels[i][j].green * 255), 0, 255);
            int blue = clamp((int)(c->pixels[i][j].blue * 255), 0, 255);

            // Convert color values to string and append to line buffer
            char color_str[20];
            sprintf(color_str, "%d %d %d ", red, green, blue);
            strcat(line, color_str);
            line_length += strlen(color_str);

            // Check if line length exceeds 70 characters
            if (line_length > 70)
            {
                // Append line to PPM string and reset line buffer
                strcat(ppm, line);
                strcat(ppm, "\n");
                line[0] = '\0';
                line_length = 0;
            }
        }
    }

    // Append remaining line to PPM string
    strcat(ppm, line);

    printf("PPM:\n%s\n", ppm);
    return ppm;
}

void PPMToFile(char *ppm, const char *filename)
{
    // Open the file for writing
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    // Write the PPM string to the file
    if (fprintf(file, "%s", ppm) < 0)
    {
        perror("Error writing to file");
        fclose(file);
        return;
    }

    // Close the file
    fclose(file);
}


#endif