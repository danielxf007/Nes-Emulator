#ifndef CPU_H
#define CPU_H
#include "data_types.h"
#include "util.h"
#include "memory_map.h"
#include "instruction.h"
#include "stdio.h"

typedef union{
    byte value;
    struct {
        bit b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1; 
    };
    
}Register8;

typedef union{
    byte value;
    struct{
        bit C:1, Z:1, I:1, D:1, B:1, X:1, V:1, N:1;
    };

}StatusRegister;

typedef struct{
    Register8 A, X, Y, SP;
    StatusRegister P;
    word PC;
}CPUContext;

class CPU6502{
    public:
        CPUContext cpu_context;
        CPU6502(MemoryMapper *mem_mapper);
        ~CPU6502();
        void init();
        void run(u32 n_cycles);
        void run();
        void reset();

    private:
        typedef void (CPU6502::*cpu_func)(void);
        bool page_crossed;
        u8 n_spend_cycles;
        cpu_func instr_vector[256];
        MemoryMapper *mem_mapper;
        inline void incrementPC();
        inline void ldReg8Inm(Register8 *reg);
        inline void ldReg8ZP(Register8 *reg);
        inline void ldReg8ZPReg8(Register8 *reg, Register8 *reg1);
        inline void ldReg8Abs(Register8 *reg);
        inline void ldReg8AbsReg8(Register8 *reg, Register8 *reg1);
        inline void ldAIdxIdtX();
        inline void ldAIdtIdxY();
        inline void stReg8ZP(Register8 *reg);
        inline void stReg8ZPReg8(Register8 *reg, Register8 *reg1);
        inline void stReg8Abs(Register8 *reg);
        inline void stReg8AbsReg8(Register8 *reg, Register8 *reg1);
        inline void stAIdxIdtX();
        inline void stAIdtIdxY();
        inline void tAReg8(Register8 *reg);
        inline void tReg8A(Register8 *reg);
        inline void tSPX();
        inline void tXSP();
        inline void pHA();
        inline void pHP();
        inline void pLA();
        inline void pLP();
        inline byte fetchInstr();
        void initInstrVector();
        void OPCode0x08();
        void OPCode0x28();
        void OPCode0x48();
        void OPCode0x68();
        void OPCode0x81();
        void OPCode0x84();
        void OPCode0x85();
        void OPCode0x86();
        void OPCode0x8A();
        void OPCode0x8C();
        void OPCode0x8D();
        void OPCode0x8E();
        void OPCode0x91();
        void OPCode0x94();
        void OPCode0x95();
        void OPCode0x96();
        void OPCode0x98();
        void OPCode0x99();
        void OPCode0x9A();
        void OPCode0x9D();
        void OPCode0xA0();
        void OPCode0xA2();
        void OPCode0xA1();
        void OPCode0xA4();
        void OPCode0xA5();
        void OPCode0xA6();
        void OPCode0xA8();
        void OPCode0xA9();
        void OPCode0xAA();
        void OPCode0xAC();
        void OPCode0xAD();
        void OPCode0xAE();
        void OPCode0xB1();
        void OPCode0xB4();
        void OPCode0xB5();
        void OPCode0xB6();
        void OPCode0xB9();
        void OPCode0xBA();
        void OPCode0xBC();
        void OPCode0xBD();
        void OPCode0xBE();
};

inline void CPU6502::incrementPC(){
    ++cpu_context.PC;
}

inline byte CPU6502::fetchInstr(){
    return mem_mapper->read(cpu_context.PC++);
}

inline void CPU6502::ldReg8Inm(Register8 *reg){
    reg->value = mem_mapper->read(cpu_context.PC++);
    cpu_context.P.Z = reg->value == 0 ? 1 : 0;
    cpu_context.P.N = reg->b7;
}

inline void CPU6502::ldReg8ZP(Register8 *reg){
    reg->value = mem_mapper->read(mem_mapper->read(cpu_context.PC++));
    cpu_context.P.Z = reg->value == 0 ? 1 : 0;
    cpu_context.P.N = reg->b7;
}

inline void CPU6502::ldReg8ZPReg8(Register8 *reg, Register8 *reg1){
    reg->value = mem_mapper->read(mem_mapper->read(cpu_context.PC++) + reg1->value);
    cpu_context.P.Z = reg->value == 0 ? 1 : 0;
    cpu_context.P.N = reg->b7;
}

inline void CPU6502::ldReg8Abs(Register8 *reg){
    word l_b = mem_mapper->read(cpu_context.PC++);
    word h_b = mem_mapper->read(cpu_context.PC++);
    reg->value = mem_mapper->read((h_b << 8) | l_b);
    cpu_context.P.Z = reg->value == 0 ? 1 : 0;
    cpu_context.P.N = reg->b7;
}

inline void CPU6502::ldReg8AbsReg8(Register8 *reg, Register8 *reg1){
    word l_b = mem_mapper->read(cpu_context.PC++);
    word h_b = mem_mapper->read(cpu_context.PC++);
    page_crossed = l_b + reg1->value > 0xFF;
    reg->value = mem_mapper->read(((h_b << 8) | l_b) + reg1->value);
    cpu_context.P.Z = reg->value == 0 ? 1 : 0;
    cpu_context.P.N = reg->b7;
}

inline void CPU6502::ldAIdxIdtX(){
    u8 addr = mem_mapper->read(cpu_context.PC++);
    addr += cpu_context.X.value;
    cpu_context.A.value = mem_mapper->read(mem_mapper->read(addr));
    cpu_context.P.Z = cpu_context.A.value == 0 ? 1 : 0;
    cpu_context.P.N = cpu_context.A.b7;    
}

inline void CPU6502::ldAIdtIdxY(){
    u16 addr = mem_mapper->read(cpu_context.PC++);
    page_crossed = (addr += cpu_context.Y.value)  > 0xFF;
    cpu_context.A.value = mem_mapper->read(addr);
    cpu_context.P.Z = cpu_context.A.value == 0 ? 1 : 0;
    cpu_context.P.N = cpu_context.A.b7;    
}

inline void CPU6502::stReg8ZP(Register8 *reg){
    mem_mapper->write(mem_mapper->read(cpu_context.PC++), reg->value);
}

inline void CPU6502::stReg8ZPReg8(Register8 *reg, Register8 *reg1){
    mem_mapper->write(mem_mapper->read(cpu_context.PC++) + reg1->value, reg->value);  
}

inline void CPU6502::stReg8Abs(Register8 *reg){
    word l_b = mem_mapper->read(cpu_context.PC++);
    word h_b = mem_mapper->read(cpu_context.PC++);
    mem_mapper->write((h_b << 8) | l_b, reg->value); 
}

inline void CPU6502::stReg8AbsReg8(Register8 *reg, Register8 *reg1){
    word l_b = mem_mapper->read(cpu_context.PC++);
    word h_b = mem_mapper->read(cpu_context.PC++);
    mem_mapper->write(((h_b << 8) | l_b) + reg1->value, reg->value);
}

inline void CPU6502::stAIdxIdtX(){
    u16 addr = mem_mapper->read(cpu_context.PC++);
    addr += cpu_context.X.value;
    mem_mapper->write(addr, cpu_context.A.value);
}

inline void CPU6502::stAIdtIdxY(){
    u16 addr = mem_mapper->read(cpu_context.PC++);
    addr += cpu_context.Y.value;
    mem_mapper->write(addr, cpu_context.A.value);    
}

inline void CPU6502::tAReg8(Register8 *reg){
    reg->value = cpu_context.A.value;
    cpu_context.P.Z = reg->value == 0 ? 1 : 0;
    cpu_context.P.N = reg->b7;    
}

inline void CPU6502::tReg8A(Register8 *reg){
    cpu_context.A.value = reg->value;
    cpu_context.P.Z = cpu_context.A.value == 0 ? 1 : 0;
    cpu_context.P.N = cpu_context.A.b7;
}

inline void CPU6502::tSPX(){
    cpu_context.X = cpu_context.SP;
    cpu_context.P.Z = cpu_context.X.value == 0 ? 1 : 0;
    cpu_context.P.N = cpu_context.X.b7;   
}

inline void CPU6502::tXSP(){
    cpu_context.SP = cpu_context.X;
}

inline void CPU6502::pHA(){
    mem_mapper->write(0x100 + cpu_context.SP.value--, cpu_context.A.value);
}

inline void CPU6502::pHP(){
    mem_mapper->write(0x100 + cpu_context.SP.value--, cpu_context.P.value);
}

inline void CPU6502::pLA(){
    cpu_context.A.value = mem_mapper->read(0x100 + ++cpu_context.SP.value);
    cpu_context.P.Z = cpu_context.A.value == 0 ? 1 : 0;
    cpu_context.P.N = cpu_context.A.b7;
}

inline void CPU6502::pLP(){
    cpu_context.P.value = mem_mapper->read(0x100 + ++cpu_context.SP.value);
}
#endif