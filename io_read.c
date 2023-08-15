#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

double io_read_file(const char *filename, int num_reads) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("fopen");
        exit(1);
    }

    char buffer[1024];
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < num_reads; ++i) {
        fread(buffer, sizeof(char), sizeof(buffer), file);
    }

    gettimeofday(&end, NULL);
    fclose(file);

    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
}
