INCLUDE_PATH = "../../../Include/"

ARCH ?=
CC = $(ARCH)g++
SUFFIX = .cpp
CFLAGS += -Wall -g

CUR_SOURCE = $(wildcard *$(SUFFIX))
CUR_TARGETS = $(patsubst %$(SUFFIX), %, $(CUR_SOURCE))

all:$(CUR_TARGETS)

# %:%.c 是一个表示与目标相同 文件的模式变量
$(CUR_TARGETS):%:%$(SUFFIX)
	$(CC) -o $@ $< -I ${INCLUDE_PATH}

.PHONY:clean all
clean:
	-rm -rf $(CUR_TARGETS)


minMax:
	g++ -o Select Select.cpp -I ${INCLUDE_PATH}

select:
	g++ -o Min_Max Min_Max.cpp -I ${INCLUDE_PATH}

