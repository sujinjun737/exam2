#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include "my_error.h" // 引入自定义错误码

// filename 是要打开的文件名，num_reads 是指定读取的次数。
double sys_read_file(const char *filename, int num_reads) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(SYSF);
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
    // tv_sec 和 tv_usec，分别表示秒数和微秒数。乘以 1e-6（即 0.000001）即可将微秒转换为秒 
}
