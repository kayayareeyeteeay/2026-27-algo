#ifndef HEAP_HPP
#define HEAP_HPP

#include "heap_exceptions.hpp"
#include <cmath>
#include <iostream>
#include <vector>

template<class I>
bool validateHeap(I first, I last);

template<class T>
class Heap {
    static const int MAX_SIZE = 12;
    T array[MAX_SIZE];
    size_t size;

    std::size_t _parent(std::size_t index);
    std::size_t _left(std::size_t index);
    std::size_t _right(std::size_t index);
    void lift_down(std::size_t index);
    void lift_up(std::size_t index);

public:
    Heap();
    bool isempty();
    void insert(T a);
    T delmax();
    T max();
};

template<class T>
Heap<T>::Heap() {
    size = 0;
}

template<class T>
bool Heap<T>::isempty() {
    return size == 0;
}

template<class T>
T Heap<T>::max() {
    if (isempty()) {
        throw EmptyHeap();
    }
    return array[0];
}



template<class T>
std::size_t Heap<T>::_parent(std::size_t index) {
    return (index-1)/2;
}

template<class T>
std::size_t Heap<T>::_left(std::size_t index) {
    return 2*index+1;
}

template<class T>
std::size_t Heap<T>::_right(std::size_t index) {
    return 2*index+2;
}

template<class T>
void Heap<T>::lift_up(std::size_t index) {
    while (index > 0 && index[array] > array[_parent(index)]) {
        std::swap(array[index], array[_parent(index)]);
        index = _parent(index);
    }
}

template<class T>
void Heap<T>::lift_down(std::size_t index) {
    while (_right(index) < size && std::max(array[_right(index)], array[_left(index)]>array[index])) {
        if (array[_left(index)] > array[_right(index)]) {
            std::swap(array[index], array[_left(index)]);
        }
        else {
            std::swap(array[index], array[_right(index)]);
        }
        

//innen meg hianyzik ha csak egy gyereke van, akkor baloldalt rakd be
    }
}

template<class T>
void Heap<T>::insert(T a) {
    array[size] = a;
    size++;
    lift_up(size-1);

}

template<class T>
T Heap<T>::delmax() {
    T tmp = array[0];
    std::swap(array[0], array[size-1]);
    lift_up(size-1);
    return tmp;

}


template<class I>
bool validateHeap(I first, I last) {
    if (last > first) {
        for (int i = 0; i < (last - first) / 2; ++i) {
            if ((first + 2 * i + 1) < last && *(first + i) < *(first + 2 * i + 1))
                return false;
            if ((first + 2 * i + 2) < last && *(first + i) < *(first + 2 * i + 2))
                return false;
        }
        return true;
    } else
        throw InvalidIterator();
}

#endif // HEAP_HPP
