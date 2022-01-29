#ifndef DATA_TYPES
#define DATA_TYPES
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint8_t bit;
typedef uint8_t nibble;
typedef uint8_t byte;
typedef uint16_t word;
typedef struct{
    byte A, X, Y, P, SP;
    word PC;
}CPUContext;
#endif
