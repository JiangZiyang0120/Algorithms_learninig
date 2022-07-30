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
template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &insertionSort(CONT<T> &) ;

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &reverseInsertionSort(CONT<T> &) ;
```
mergeSort
```c++
template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &mergeSort(CONT<T> &);

template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &reverseMergeSort(CONT<T> &);
```
heapSort
```c++
template <typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &heapSort(CONT<T> &);

template <typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &reverseHeapSort(CONT<T> &);
```
quickSort
```c++
//By using random sort
template<typename T,
        template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &quickSort(CONT<T> &);

template<typename T,
template <typename ELEM,typename = std::allocator<ELEM> >class CONT=std::vector>
CONT<T> &reverseQuickSort(CONT<T> &);
```