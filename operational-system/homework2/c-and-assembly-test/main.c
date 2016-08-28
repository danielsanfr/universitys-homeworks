#include <stdio.h>

/*
 * declaring add as extern tells the compiler that the definition
 * can be found in a seperate module
 */
extern int add(int a, int B);

int main() {
    int ret = add(10, 20);
    printf("add returned %d\n", ret);
    return 0;
}
