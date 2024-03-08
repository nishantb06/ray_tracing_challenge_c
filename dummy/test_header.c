# include <stdio.h>
# include "header.h"

int main() {
    int result = add(3, 4);
    if (result == 7) {
        printf("add function test passed!\n");
    } else {
        printf("add function test failed!\n");
    }
    return 0;
}