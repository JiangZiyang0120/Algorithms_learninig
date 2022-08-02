INCLUDE_PATH = "../../../Include/"

ARCH ?=
CC = $(ARCH)gcc
SUFFIX = .cpp
CFLAGS += -Wall -g

CUR_SOURCE = $(wildcard *$(SUFFIX))
CUR_TARGETS = $(patsubst %$(SUFFIX), %, $(CUR_SOURCE))

all:$(CUR_TARGETS)

# %:%.c 是一个表示与目标相同 文件的模式变量
$(CUR_TARGETS):%:%$(SUFFIX)
	$(CC) -o $@ $< I ${INCLUDE_PATH}

# 指定伪目标
.PHONY:clean all
clean:
	-rm -rf $(CUR_TARGETS)

insertionSort:
	g++ -o Insertion_Sort Insertion_Sort.cpp -I ${INCLUDE_PATH}

radixSort:
	g++ -o Radix_Sort Radix_Sort.cpp -I ${INCLUDE_PATH}

heapSort:
	g++ -o Heap_Sort Heap_Sort.cpp -I ${INCLUDE_PATH}

mergeSort:
	g++ -o Merge_Sort Merge_Sort.cpp -I ${INCLUDE_PATH}

quickSort:
	g++ -o Quick_Sort Quick_Sort.cpp -I ${INCLUDE_PATH}

countingSort:
	g++ -o Counting_Sort Counting_Sort.cpp -I ${INCLUDE_PATH}

bucketSort:
	g++ -o Bucket_Sort Bucket_Sort.cpp -I ${INCLUDE_PATH}