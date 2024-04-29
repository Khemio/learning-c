#include <stddef.h>

struct array {
    size_t n;    // number of elements used
    size_t size; // size of data block
    int *data;   // data block
};

// Basic dynamic array type.
//
// This acts like an unboundedly large array
// of ints, all initialized to zero.
//
// The trick is to resize the underlying array
// whenever the caller asks for a location that
// isn't in the array already.

// Create a new array initialized to 0.
struct array *arrayCreate(void);

// Return the value in an array at given position.
int arrayGet(struct array *, size_t position);

// Set the value in an array at given position.
// Returns new value.
int arraySet(struct array *, size_t position, int value);

// Free all space used by an array.
void arrayDestroy(struct array *);