#include <stdio.h>

int max(int nums[], int len) {
    int i;
    int max = nums[0];
    
    for (i = 1; i < len; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    return max;
}

int min(int nums[], int len) {
    int i;
    int min = nums[0];
    
    for (i = 1; i < len; i++) {
        if (nums[i] < min) {
            min = nums[i];
        }
    }
    return min;
}

int sum(int nums[], int len) {
    int i;
    int sum = 0;
    
    for (i = 0; i < len; i++) {
        sum += nums[i];
    }
    return sum;
}

int prod(int nums[], int len) {
    int i;
    int prod = 1;
    
    for (i = 0; i < len; i++) {
        prod *= nums[i];
    }
    return prod;
}

int main() {
    int nums[] = {1, 3, 11, 5, 7};
    int len = sizeof(nums) / sizeof(nums[0]);

    printf("Maximum of the array: %d\n", max(nums, len));
    printf("Minimum of the array: %d\n", min(nums, len));
    printf("Sum of the array: %d\n", sum(nums, len));
    printf("Product of the array: %d\n", prod(nums, len));

    
    
    return 0;
}
