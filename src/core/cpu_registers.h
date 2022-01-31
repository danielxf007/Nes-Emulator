#include "data_types.h"

typedef struct Register8{
    byte value;
    Register8() {value = 0;};
};

typedef union ProcessorStatus{
    byte value;
    struct{
        bit C:1, Z:1, I:1, D:1, B:1, X:1, V:1, N:1;
    };
    ProcessorStatus() {value = 0x20;};
};

//
class PC{
    private:
        word value;
    public:
        PC();
        inline word getValue();
        inline void increment();
        inline void reset();
};

PC::PC(){
    value = 0;
}

inline word PC::getValue(){
    return value; 
}

inline void PC::increment(){
    ++value;
}

inline void PC::reset(){
    value = 0;
}
//
class SP{
    private:
        byte value;
    public:
        SP();
        inline byte getValue();
        inline void increment();
        inline void reset();
};

SP::SP(){
    value = 0;
}

inline byte SP::getValue(){
    return value; 
}

inline void SP::increment(){
    ++value;
}

inline void SP::reset(){
    value = 0;
}
//