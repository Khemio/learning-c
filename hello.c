#include <stdio.h>

int main() {
    int i;
    int n = 10;
    int result;

    puts("Now I will count from 1 to 10");
    for(i = 1; i <= n; i++) {
        result += i;
        printf("%d\n", result);
    }
    
    return 0;
}
