#ifndef UTIL_H
#define UTIL_H
#include "data_types.h"

template<class T> inline bit getBit(T number, u8 bit_pos){
    return ((number & (static_cast<T>(0x1) << bit_pos)) >> bit_pos);
}

template<class T> inline bit getNBits(T number, u8 n_bits, u8 pos){
    return ((number & ((~(~(static_cast<T>(0)) << n_bits)) << pos)) >> pos);
}

template<class T> inline bit getNibble(T number, u8 nibble_pos){
    return ((number & (static_cast<T>(0xF) << (4*nibble_pos))) >> (4*nibble_pos));
}

template<class T> inline void setBit(T &number, bit value, u8 bit_pos){
    number = (number & ~(value << bit_pos)) | (value << bit_pos);
}

template <class T> inline void clearPointer(T *p){
    delete p;
    p = nullptr;
}

#endif