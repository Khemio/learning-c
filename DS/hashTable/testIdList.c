#include <stdio.h>

#include "idList.h"

int main(void) {
    IDList list;
    int ids[] = {123456789, 987654321, 102938475};

    list = IDListCreate(3, ids);

    printf("%d\n", IDListContains(list, ids[0]));
    printf("%d\n", IDListContains(list, ids[1]));
    printf("%d\n", IDListContains(list, ids[2]));

    IDListDestroy(list);





    return 0;
}