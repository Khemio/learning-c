#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char title[41];
    int length;
    int plays;
} TRACK;

int cmp(const void* a, const void* b) {
    TRACK *left = (TRACK *) a;
    TRACK *right = (TRACK *) b;

    if (left->plays != right->plays) {
        return -(left->plays - right->plays);
    }

    if (left->plays != right->plays) {
        return left->length - right->length;
    }

    return strcmp(left->title, right->title);

}

int main(int argc, char **argv) {
    TRACK tracks[20];
    int size = 0;
    char line[61];
    FILE* fd;

    if (argc < 2) {
        fprintf(stderr,"Please provide an input file as an argument.\n");
        return 1;
    }
    if (argc < 3) {
        fprintf(stderr, "Please provide an output file as an argument.\n");
        return 3;
    }

    fd = fopen(argv[1], "r");
    if (fd == NULL) {
        fprintf(stderr,"Could not open an input file\n");
        return 2;
    }

    while (fgets(line, 100, fd)) {
        strcpy(tracks[size].title, strtok(line, ";"));
        // strcat(tracks[size].title, "\0");
        tracks[size].length = atoi(strtok(NULL, ";"));
        tracks[size].plays = atoi(strtok(NULL, ";"));
        size++;
    }
    fclose(fd);

    // Sort

    qsort(tracks, size, sizeof(TRACK), cmp);

    for (int i = 0; i < size; i++) {
        printf("%s %d %d\n", tracks[i].title, tracks[i].length, tracks[i].plays);
    }

    fd = fopen(argv[2], "w");

    if (fd == NULL) {
        fprintf(stderr, "Could not open an output file\n");
        return 4;
    }

    for (int i = 0; i < size; i++) {
        fprintf(fd, "%s;%d;%d\n", tracks[i].title, tracks[i].length, tracks[i].plays);
    }

    fclose(fd);

    return EXIT_SUCCESS;
}