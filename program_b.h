/*
接收3个参数：文件名、线程数、每个线程读取该文件的次数（即1中的n）
调用io_read.so接口函数，将耗时记录下来
 */
#ifndef IO_READ_H
#define IO_READ_H

void sigint_handler(int signum); // 用于处理"Ctrl+c"信号
void *thread_function(void *arg); // 线程函数的定义，执行了读取文件的操作，计算了时间，并将线程执行时间存储在 thread_times 数组中。
int main(int argc, char *argv[]); // main 函数的定义，它接收命令行参数，设置了 Ctrl+C 信号处理程序，然后创建线程来执行文件读取任务。

#endif