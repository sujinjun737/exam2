//库函数调用
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dlfcn.h> // For dynamic loading
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include "my_error.h"

volatile sig_atomic_t exit_requested = 0;

// 用于处理"Ctrl+c"信号
void sigint_handler(int signum) {
    exit_requested = 1;
}

// 用于指向读取函数的原型
typedef double (*ReadFunction)(const char *, int);

struct ThreadArgs {
    const char *filename; // 文件名
    int num_reads; // 读取次数
    int thread_id; // 现场ID
};

double thread_times[100]; // 用于存储每个线程的执行时间

void *thread_function(void *arg) {
    struct ThreadArgs *thread_args = (struct ThreadArgs *)arg;
    const char *filename = thread_args->filename;
    int num_reads = thread_args->num_reads;
    int thread_id = thread_args->thread_id;

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    void *handle = dlopen("./io_read.so", RTLD_LAZY); // Load io_read.so
    if (!handle) {
        fprintf(stderr, "Error loading io_read.so: %s\n", dlerror());
        exit(ELIO);
    }

    ReadFunction read_func = (ReadFunction)dlsym(handle, "io_read_file");
    if (!read_func) {
        fprintf(stderr, "Error loading function from io_read.so: %s\n", dlerror());
        dlclose(handle);
        exit(ELFIO);
    }

    double time_taken = read_func(filename, num_reads);
    printf("Thread %d: Time taken: %f seconds\n", thread_id, time_taken);

    dlclose(handle);

    gettimeofday(&end_time, NULL);
    thread_times[thread_id] = (end_time.tv_sec - start_time.tv_sec) + 
                              (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <filename> <num_threads> <num_reads>\n", argv[0]);
        return WNP;
    }

    signal(SIGINT, sigint_handler);

    const char *filename = argv[1];
    int num_threads = atoi(argv[2]);
    int num_reads = atoi(argv[3]);

    pthread_t threads[num_threads];
    struct ThreadArgs thread_args[num_threads];

    printf("我是库函数调用！\n");
    // 循环创建线程
    for (int i = 0; i < num_threads; ++i) {
        thread_args[i].filename = filename;
        thread_args[i].num_reads = num_reads;
        thread_args[i].thread_id = i;
        pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
    }
    double total_time = 0.0; // 所有线程累加耗时
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], NULL);
        total_time += thread_times[i]; 
    }

    printf("Program_b total time taken by all threads: %f seconds\n", total_time);

    //以tm结构体获取当前时间
    time_t raw_time;
    struct tm *time_info;
    time(&raw_time);
    time_info = localtime(&raw_time);
    // 格式化为 "YYYY-MM-DD HH:MM:SS"
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", time_info);
    // 将程序运行信息写入日志文件
    FILE *log_file = fopen("performance_log.txt", "a");
    if (log_file) {
        fprintf(log_file, "Timestamp: %s\n", time_str);
        fprintf(log_file, "Command: %s %s %d %d\n", "./program_b", filename, num_threads, num_reads);
        fprintf(log_file, "Progtam_b total time taken by all threads: %f seconds\n", total_time);
        fclose(log_file);
    }
    return 0;
}
