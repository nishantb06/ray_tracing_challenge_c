# include <stdio.h>
# include "header.h"

void test_add() {
    int result = add(3, 4);
    if (result == 7) {
        printf("add function test passed!\n");
    } else {
        printf("add function test failed!\n");
    }
}

int main() {
    test_add();
    return 0;
}