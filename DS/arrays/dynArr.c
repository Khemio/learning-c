#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "dynArr.h"

// Invariant: size == number of elements in data
struct dynArr {
    size_t size; // number of elements in data;
    int *data;   // malloc'd block
};

#define SIZE_INITIAL (16)
#define SIZE_MULTIPLIER (2)    // Minimum ratio to grow by.

// Create a new array initialized to 0.
struct array *
arrayCreate(void)
{
    struct array *a = malloc(sizeof(struct array));
    assert(a);

    a->size = SIZE_INITIAL;

    // calloc zeroes out the array
    a->data = calloc(a->size, sizeof(int));

    assert(a->data);

    return a;
}

// Expand array if needed to include position.
static void
arrayExpand(struct array *a, size_t position)
{
    if(position >= a->size) {
        // expansion needed
        size_t bigger = a->size * SIZE_MULTIPLIER;

        if(position >= bigger) {
            // even more expansion needed
            bigger = position + 1;
        }

        // Breaks invariant, we will fix later
        // after using a->size to zero out new space.
        a->data = realloc(a->data, sizeof(int) * bigger);

        memset(&a->data[a->size], 0, sizeof(int) * (bigger - a->size));

        a->size = bigger;
    }
}

// Return the value in an array at given position.
int
arrayGet(struct array *a, size_t position)
{
    if(position >= a->size) {
        // No need to expand, just return the default value.
        return 0;
    } else {
        return a->data[position];
    }
}

// Set the value in an array at given position.
int
arraySet(struct array *a, size_t position, int value)
{
    arrayExpand(a, position);

    return a->data[position] = value;
}

// Free all space used by an array.
void 
arrayDestroy(struct array *a)
{
    free(a->data);
    free(a);
}