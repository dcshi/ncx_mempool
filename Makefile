CC=gcc
CXX=g++
INC+= 
LIB+= 

#判断系统架构(32bit, 64bit)
ARCH := $(shell getconf LONG_BIT)
ifeq ($(ARCH),64)
CFLAGS+= -DNCX_PTR_SIZE=8
else
CFLAGS+= -DNCX_PTR_SIZE=4
endif

#CFLAGS+= -pipe  -O0 -Wall -g3 -ggdb3 
CFLAGS+= -pipe  -O3 
#定义是否打印日志
CFLAGS+= -DLOG_LEVEL=4 
#是否与malloc类似模拟脏数据
#CFLAGS+= -DNCX_DEBUG_MALLOC
#是否自动合并碎片
CFLAGS+= -DPAGE_MERGE 

TARGET=pool_test
ALL:$(TARGET)

OBJ= ncx_slab.o

$(TARGET):$(OBJ)  main.o 
	$(CC)	$(CFLAGS) -o $@ $^ $(LIB)

pool_bench:$(OBJ) bench.o
	$(CC)	$(CFLAGS) -o $@ $^ $(LIB)

%.o: %.c
	$(CC)  $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f *.o
	rm -f $(TARGET) pool_bench

install:
