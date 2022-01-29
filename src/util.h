#ifndef UTIL_H
#define UTIL_H
#include "data_types.h"

template<class T> inline bit getBit(T number, u8 bit_pos){
    return ((number & (static_cast<T>(0x1) << bit_pos)) >> bit_pos);
}

template<class T> inline void setBit(T &number, bit value, u8 bit_pos){
    number = (number & ~(value << bit_pos)) | (value << bit_pos);
}

template <class T> inline void clearPointer(T *p){
    delete p;
    p = nullptr;
}

#endif