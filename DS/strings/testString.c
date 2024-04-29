#include <stdio.h>
#include <string.h>

#include "myString.h"

int main(void) {
    char *hello = "Hello, World!";

    String hi;

    hi = makeString(hello);

    printf("%llu\n", strlen(hello));
    printf("%d\n", stringLength(hi));

    printf("%c\n", hello[4]);
    printf("%c\n", stringCharAt(hi, 4));

    destroyString(hi);

    return 0;
}