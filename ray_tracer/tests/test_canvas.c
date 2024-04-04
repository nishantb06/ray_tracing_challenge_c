# include "../src/canvas.h"
# include <assert.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

void test_color() {
    Color c = Color_(-0.5f, 0.4f, 1.7f);
    assert(c.red == -0.5f);
    assert(c.green == 0.4f);
    assert(c.blue == 1.7f);
    printf("test_color passed\n");
}

void test_add_colors() {
    Color c1 = Color_(0.9f, 0.6f, 0.75f);
    Color c2 = Color_(0.7f, 0.1f, 0.25f);
    Color c3 = AddColor(c1, c2);
    assert((c3.red - 1.6f)<0.00001);
    assert((c3.green - 0.7f)<0.00001);
    assert((c3.blue - 1.0f)<0.00001);
    printf("test_add_colors passed\n");
}

void test_subtract_colors() {
    Color c1 = Color_(0.9f, 0.6f, 0.75f);
    Color c2 = Color_(0.7f, 0.1f, 0.25f);
    Color c3 = SubtractColor(c1, c2);
    assert(fabs(c3.red - 0.2f) < 0.00001);
    assert(fabs(c3.green - 0.5f) < 0.00001);
    assert(fabs(c3.blue - 0.5f) < 0.00001);
    printf("test_subtract_colors passed\n");
}


void test_multiply_colors() {
    Color c1 = Color_(1.0f, 0.2f, 0.4f);
    Color c2 = Color_(0.9f, 1.0f, 0.1f);
    Color c3 = MultiplyColor(c1, c2);
    assert(fabs(c3.red - 0.9f) < 0.00001);
    assert(fabs(c3.green - 0.2f) < 0.00001);
    assert(fabs(c3.blue - 0.04f) < 0.00001);
    printf("test_multiply_colors passed\n");
}

void test_scaler_multiply() {
    Color c1 = Color_(0.2f, 0.3f, 0.4f);
    ScalarMultiplyColor(&c1, 2.0f);
    assert(c1.red == 0.4f);
    assert(c1.green == 0.6f);
    assert(c1.blue == 0.8f);
    printf("test_scaler_multiply passed\n");
}

void test_scaler_divide()
{
    Color c1 = Color_(1.0f, -2.0f, 3.0f);
    ScalarDivideColor(&c1, 2.0f);
    assert(c1.red == 0.5f);
    assert(c1.green == -1.0f);
    assert(c1.blue == 1.5f);
    printf("test_scaler_divide passed\n");
}

void TestColors() {
    test_color();
    test_add_colors();
    test_subtract_colors();
    test_multiply_colors();
    test_scaler_divide();
    test_scaler_multiply();
}

// “​Scenario​ : Creating a canvas​ 
// ​Given​ c ← canvas(10, 20)​
// ​Then​ c.width = 10​
// ​And​ c.height = 20​
// ​And​ every pixel of c is color(0, 0, 0)”

void test_canvas() {
    Canvas c = Canvas_(10, 20);
    assert(c.width == 10);
    assert(c.height == 20);
    for (int i = 0; i < c.width; i++) {
        for (int j = 0; j < c.height; j++) {
            assert(c.pixels[i][j].red == 0.0f);
            assert(c.pixels[i][j].green == 0.0f);
            assert(c.pixels[i][j].blue == 0.0f);
        }
    }
    printf("test_canvas passed\n");
}

/*
“​Scenario​: Writing pixels to a canvas​ 
​Given​ c ← canvas(10, 20)​ 
​And​ red ← color(1, 0, 0)​ 
​When​ write_pixel(c, 2, 3, red)​   ​
Then​ pixel_at(c, 2, 3) = red”
*/

void test_write_pixel() {
    Canvas c = Canvas_(10, 20);
    Color red = Color_(1.0f, 0.0f, 0.0f);
    WritePixel(&c, 2, 3, red);
    assert(c.pixels[2][3].red == 1.0f);
    assert(c.pixels[2][3].green == 0.0f);
    assert(c.pixels[2][3].blue == 0.0f);
    printf("test_write_pixel passed\n");
}
/*
Scenario​: Constructing the PPM header​ 
Given​ c ← canvas(5, 3)​ 
​When​ ppm ← canvas_to_ppm(c)​   ​
Then​ lines 1-3 of ppm are​ 
​"""​​ 
P3​​ 
5 3​​ 
255​​ ​
"""​
*/

void test_canvas_to_ppm()
{
    Canvas c = Canvas_(5, 3);
    char *ppm = CanvasToPPM(&c);
    const char *expected_ppm = "P3\n5 3\n255\n";

    // Make a copy of the actual PPM string
    char *ppm_copy = strdup(ppm);

    // Split the expected and actual PPM strings into lines
    char *expected_line, *actual_line;
    expected_line = strtok(strdup(expected_ppm), "\n");
    actual_line = strtok(ppm_copy, "\n");

    // Compare line by line
    while (expected_line != NULL && actual_line != NULL)
    {
        printf("Expected line: %s\n", expected_line);
        printf("Actual line: %s\n", actual_line);
        assert(strcmp(expected_line, actual_line) == 0);
        expected_line = strtok(NULL, "\n");
        actual_line = strtok(NULL, "\n");
    }

    // Ensure both expected and actual lines are exhausted
    assert(expected_line == NULL && actual_line == NULL);

    // Free the memory allocated for the copied PPM string
    free(ppm_copy);

    printf("test_canvas_to_ppm passed\n");
}

void TestCanvas()
{
    test_canvas();
    test_write_pixel();
    // test_canvas_to_ppm();
}

int main()
{
    TestColors();
    TestCanvas();
    return 0;
}
