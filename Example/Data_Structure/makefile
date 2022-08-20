INCLUDE_PATH = "../../../Include/"

ARCH ?=
CC = $(ARCH)g++
SUFFIX = .cpp
OTHERFIX = .html
CFLAGS += -Wall -g

CUR_SOURCE = $(wildcard *$(SUFFIX))
CUR_TARGETS = $(patsubst %$(SUFFIX), %, $(CUR_SOURCE)) + $(wildcard *$(OTHERFIX))

all:$(CUR_TARGETS)

# %:%.c 是一个表示与目标相同 文件的模式变量
$(CUR_TARGETS):%:%$(SUFFIX)
	$(CC) -o $@ $< -I ${INCLUDE_PATH}

.PHONY:clean all
clean:
	-rm -rf $(CUR_TARGETS)

queue:
	g++ -o Queue Queue.cpp -I ${INCLUDE_PATH}

stack:
	g++ -o Stack Stack.cpp -I ${INCLUDE_PATH}

list:
	g++ -o List List.cpp -I ${INCLUDE_PATH}