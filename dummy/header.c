# include <stdio.h>
// include the header.h file
# include "header.h"

int  test_add(int a, int b) {
    return a + b;
}

int main() {
    printf("Hello, World!\n");
    int c = add(1, 2);
    printf("1 + 2 = %d\n", c);
    return 0;
}