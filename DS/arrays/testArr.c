#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "dynArr.h"

int
main(int argc, char **argv)
{

    if(argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return 1;
    }

    size_t n = strtoull(argv[1], 0, 0);

    struct array *a = arrayCreate();

    for(size_t i = 0; i < n; i++) {
        assert(arrayGet(a, i) == 0);
        assert(arraySet(a, i, i) == i);
        assert(arrayGet(a, i) == i);
    }

    // one more pass to make sure nothing weird happened
    for(size_t i = 0; i < n; i++) {
        assert(arrayGet(a, i) == i);
    }

    // test expansion by large amount
    assert(arraySet(a, 3*n, 12) == 12);
    assert(arraySet(a, 3*n+1, 13) == 13);

    // test no-expansion heuristic for arrayGet
    assert(arrayGet(a, 1ULL << 62) == 0);

    return 0;
}