.PHONY: all clean

#编译参数
CC := gcc
CFLAGS := -Wall -pthread
LDFLAGS_SYS := -ldl -L.-lsys_read
LDFLAGS_IO := -ldl -L.-lso_read
SHARE := -fPIC -shared -o

#共享库
SOURCE_SYS := sys_read.c
LIB_SYS := sys_read.so
SOURCE_IO := io_read.c
LIB_IO := io_read.so

#可执行文件
OBJ_A := program_a
OBJ_B := program_b

all: $(LIB_SYS) $(LIB_IO) $(OBJ_A) $(OBJ_B)

$(LIB_SYS): $(SOURCE_SYS)
	$(CC) $(CFLAGS) $(SHARE) $(LIB_SYS) $(SOURCE_SYS)

$(LIB_IO): $(SOURCE_IO)
	$(CC) $(CFLAGS) $(SHARE) $(LIB_IO) $(SOURCE_IO)

$(OBJ_A): $(OBJ_A).c 
	$(CC) $(CFLAGS) -o $(OBJ_A) $(OBJ_A).c $(LDFLAGS_SYS)

$(OBJ_B): $(OBJ_B).c 
	$(CC) $(CFLAGS) -o $(OBJ_B) $(OBJ_B).c $(LDFLAGS_IO)

clean:
	rm -f $(LIB_SYS) $(LIB_IO) $(OBJ_A) $(OBJ_B)
