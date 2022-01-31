#include "data_types.h"

class CPU6502{
    private:
        CPUContext cpu_context;
    public:
        CPU6502();
        void reset();
        CPUContext *getContext();
        inline bit getBit(byte b, u8 n);
        inline bit setBit(bit value,u8 n, byte &b);
        inline void incrementPC();
};

inline bit CPU6502::getBit(byte b, u8 n){
    return ((b & (0x1 << n)) >> n);
}

inline bit CPU6502::setBit(bit value, u8 n, byte &b){
    b = (b & ~(value << n)) | (value << n);
}

inline void CPU6502::incrementPC(){
    ++cpu_context.PC;   
}