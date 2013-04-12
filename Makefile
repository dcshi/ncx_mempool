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

#CFLAGS+= -pipe  -O0 -W -Wall -Wpointer-arith -Wno-unused-parameter -Wpointer-sign -g -ggdb3
CFLAGS+= -pipe  -O0 -Wall -g3 -ggdb3 
#CFLAGS+= -pipe  -O3 -Wall
#定义是否打印日志
CFLAGS+= -DLOG_LEVEL=4
#是否与malloc类似模拟脏数据
#CFLAGS+= -DNCX_DEBUG_MALLOC

TARGET=pool_test
ALL:$(TARGET)

OBJ= .objs/ncx_slab.o

$(TARGET):$(OBJ) .objs/main.o 
	$(CC)	$(CFLAGS) -o $@ $^ $(LIB)

pool_bench:$(OBJ)  .objs/bench.o
	$(CC)	$(CFLAGS) -o $@ $^ $(LIB)

.objs/%.o: %.c
	$(CC)  $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -f .objs/*
	rm -f $(TARGET)

install:
