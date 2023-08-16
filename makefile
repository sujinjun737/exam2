.PHONY: all clean

#编译参数
CC := gcc
CFLAGS := -Wall -pthread -o
LDFLAGS_SYS := -ldl -L.-lsys_read
LDFLAGS_IO := -ldl -L.-lio_read
SHARE := -fPIC -shared -o

#源码
SOURCE_SYS := sys_read.c
SOURCE_IO := io_read.c
SOURCE_A := program_a.c #系统调用
SOURCE_B := program_b.c #I/O库函数调用

#共享库
LIB_SYS := sys_read.so
LIB_IO := io_read.so

#可执行文件
OBJ_A := program_a
OBJ_B := program_b


all: $(LIB_SYS) $(LIB_IO) $(OBJ_A) $(OBJ_B)

$(LIB_SYS): $(SOURCE_SYS)
	$(CC) $(CFLAGS) $(SHARE) $(LIB_SYS) $(SOURCE_SYS)

$(LIB_IO): $(SOURCE_IO)
	$(CC) $(CFLAGS) $(SHARE) $(LIB_IO) $(SOURCE_IO)

$(OBJ_A): $(SOURCE_A)
	$(CC) $(CFLAGS) $(OBJ_A) $(SOURCE_A) $(LDFLAGS_SYS)

$(OBJ_B): $(SOURCE_B) 
	$(CC) $(CFLAGS) $(OBJ_B) $(SOURCE_B) $(LDFLAGS_IO)

clean:
	rm -f $(LIB_SYS) $(LIB_IO) $(OBJ_A) $(OBJ_B)
