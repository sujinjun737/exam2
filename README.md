# 项目介绍

## 任务说明

编写程序，测试 系统调用（read相关函数）和标准I/O库函数（fread）的性能对比

1 编写两个so（sys_read.so、io_read.so），分别使用系统调用和库函数来读取某个文件n次，返回耗时（读该文件n次所花的时间）

2 编写程序progam_a和progam_b，分别调用上述的so

2.1 progam_a和progam_b都接收3个参数：文件名、线程数、每个线程读取该文件的次数（即1中的n）

2.2 progam_a和progam_b的线程函数：分别调用sys_read.so和io_read.so接口函数，将耗时记录下来

2.3 progam_a和progam_b的主线程（main函数）：创建线程，等所有线程执行完，printf每个线程中记录的耗时和所有线程累加耗时，再接收ctrl+c优雅退出（使用信号）

3 其他要求：
3.1 编写makefile一次性编译上述所有so和程序

## 文件与项目结构说明

### io_read.c sys_read.c

这是两个动态链接库 分别包含函数io_read_file和sys_read_file

### program_a

使用系统调用

### program_b

使用标准I/O库函数调用

### makefile

编译，make命令后生成io_read.so、sys_read、program_a和program_b

### big.pdf small.pdf small.txt

我个人使用的读取测试文件，大中小

### 测试ceshi.sh

测试脚本，方便重复运行

### my_error

自定义错误码

## 使用说明

### 运行示例

```bash
make 
./ceshi.sh 10 #交替运行program_a和program_b程序10次
```

### 输出结果

可见performance_log.txt日志文件或者终端输出
