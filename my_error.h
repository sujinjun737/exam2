/*
错误码定义
 */

#ifndef MY_ERROR_H
#define MY_ERROR_H

#define WNP 1 // Wrong number of parameters
#define ELS 2 // Error loading sys_read.so
#define ELIO 3 // Error loading io_read.so
#define ELFS 4 // Error loading function from sys_read.so
#define ELFIO 5 // Error loading function from io_read.so
#define IOF 6 // I/O library function call failed to open
#define SYSF 7 // System call failed to open

#endif