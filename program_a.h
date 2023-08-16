// 系统调用
#ifndef PROGRAM_A_H
#define PROGRAM_A_H

void sigint_handler(int signum); // 用于处理"Ctrl+c"信号
void *thread_function(void *arg); // 线程函数的定义，执行了读取文件的操作，计算了时间，并将线程执行时间存储在 thread_times 数组中。

#endif