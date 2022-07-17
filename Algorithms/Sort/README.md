# Sort Function

## Include
suppose the lib's address is `{Algorithms}` in your host\
Then you can include the sort chunk by the following declaration
```c++
#include "{Algorithms}/Algorithms/Sort.h"
```

## Function
insertionSort
```c++
template <typename T>
std::vector<T> &insertionSort(std::vector<T> &V);

template <typename T>
std::vector<T> &reverseInsertionSort(std::vector<T> &V);
```
mergeSort
```c++
template<typename T>
std::vector<T> &mergeSort(std::vector<T> &A);

template<typename T>
std::vector<T> &reverseMergeSort(std::vector<T> &A);
```
heapSort
```c++
template <typename T>
std::vector<T> &heapSort(std::vector<T> &A);

template <typename T>
std::vector<T> &reverseHeapSort(std::vector<T> &A);
```
quickSort
```c++
template<typename T>
std::vector<T> &quickSort(std::vector<T> &A);

template<typename T>
std::vector<T> &reverseQuickSort(std::vector<T> &A);
```