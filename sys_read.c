#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

double sys_read_file(const char *filename, int num_reads) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    char buffer[1024];
    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < num_reads; ++i) {
        read(fd, buffer, sizeof(buffer));
    }

    gettimeofday(&end, NULL);
    close(fd);

    return (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
}
