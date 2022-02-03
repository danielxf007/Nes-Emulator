#include "cpu.h"

CPU6502::CPU6502(MemoryMapper *mem_mapper){
    cpu_context.A.value = 0;
    cpu_context.X.value = 0;
    cpu_context.Y.value = 0;
    cpu_context.P.value = 0x20;
    cpu_context.SP.value = 0xFF;
    cpu_context.PC = 0x8000;
    n_spend_cycles = 0;
    page_crossed  = false;
    this->mem_mapper = mem_mapper;
}

CPU6502::~CPU6502(){
}

void CPU6502::initInstrVector(){
    instr_vector[0x08] = &CPU6502::OPCode0x08;
    instr_vector[0x28] = &CPU6502::OPCode0x28;
    instr_vector[0x48] = &CPU6502::OPCode0x48;
    instr_vector[0x68] = &CPU6502::OPCode0x68;
    instr_vector[0x81] = &CPU6502::OPCode0x81;
    instr_vector[0x84] = &CPU6502::OPCode0x84;
    instr_vector[0x85] = &CPU6502::OPCode0x85;
    instr_vector[0x86] = &CPU6502::OPCode0x86;
    instr_vector[0x8A] = &CPU6502::OPCode0x8A;
    instr_vector[0x8C] = &CPU6502::OPCode0x8C;
    instr_vector[0x8D] = &CPU6502::OPCode0x8D;
    instr_vector[0x8E] = &CPU6502::OPCode0x8E;
    instr_vector[0x91] = &CPU6502::OPCode0x91;
    instr_vector[0x94] = &CPU6502::OPCode0x94;
    instr_vector[0x95] = &CPU6502::OPCode0x95;
    instr_vector[0x96] = &CPU6502::OPCode0x96;
    instr_vector[0x98] = &CPU6502::OPCode0x98;
    instr_vector[0x99] = &CPU6502::OPCode0x99;
    instr_vector[0x9A] = &CPU6502::OPCode0x9A;
    instr_vector[0x9D] = &CPU6502::OPCode0x9D;
    instr_vector[0xA0] = &CPU6502::OPCode0xA0;
    instr_vector[0xA2] = &CPU6502::OPCode0xA2;
    instr_vector[0xA1] = &CPU6502::OPCode0xA1;
    instr_vector[0xA4] = &CPU6502::OPCode0xA4;
    instr_vector[0xA5] = &CPU6502::OPCode0xA5;
    instr_vector[0xA6] = &CPU6502::OPCode0xA6;
    instr_vector[0xA8] = &CPU6502::OPCode0xA8;
    instr_vector[0xA9] = &CPU6502::OPCode0xA9;
    instr_vector[0xAA] = &CPU6502::OPCode0xAA;
    instr_vector[0xAC] = &CPU6502::OPCode0xAC;
    instr_vector[0xAD] = &CPU6502::OPCode0xAD;
    instr_vector[0xAE] = &CPU6502::OPCode0xAE;
    instr_vector[0xB1] = &CPU6502::OPCode0xB1;
    instr_vector[0xB4] = &CPU6502::OPCode0xB4;
    instr_vector[0xB5] = &CPU6502::OPCode0xB5;
    instr_vector[0xB6] = &CPU6502::OPCode0xB6;
    instr_vector[0xB9] = &CPU6502::OPCode0xB9;
    instr_vector[0xBA] = &CPU6502::OPCode0xBA;
    instr_vector[0xBC] = &CPU6502::OPCode0xBC;
    instr_vector[0xBD] = &CPU6502::OPCode0xBD;
    instr_vector[0xBE] = &CPU6502::OPCode0xBE;
}

void CPU6502::init(){
    initInstrVector();
}

void CPU6502::reset(){
    cpu_context.A.value = 0;
    cpu_context.X.value = 0;
    cpu_context.Y.value = 0;
    cpu_context.P.value = 0x20;
    cpu_context.SP.value = 0xFF;
    cpu_context.PC = 0x8000;
}


void CPU6502::run(){
    (this->*instr_vector[fetchInstr()])();
}


void CPU6502::OPCode0x08(){
    pHP();
    n_spend_cycles = n_cycles[0x08];
}

void CPU6502::OPCode0x28(){
    pLP();
    n_spend_cycles = n_cycles[0x28];
}

void CPU6502::OPCode0x48(){
    pHA();
    n_spend_cycles = n_cycles[0x48];
}

void CPU6502::OPCode0x68(){
    pLA();
    n_spend_cycles = n_cycles[0x68];
}

void CPU6502::OPCode0x81(){
    ldAIdxIdtX();
    n_spend_cycles = n_cycles[0x81];
}

void CPU6502::OPCode0x84(){
    stReg8ZP(&(cpu_context.Y));
    n_spend_cycles = n_cycles[0x84];
}

void CPU6502::OPCode0x85(){
    stReg8ZP(&(cpu_context.A));
    n_spend_cycles = n_cycles[0x85];
}

void CPU6502::OPCode0x86(){
    stReg8ZP(&(cpu_context.X));
    n_spend_cycles = n_cycles[0x86];
}

void CPU6502::OPCode0x8A(){
    tReg8A(&(cpu_context.X));
    n_spend_cycles = n_cycles[0x8A];
}

void CPU6502::OPCode0x8C(){
    stReg8Abs(&(cpu_context.Y));
    n_spend_cycles = n_cycles[0x8C];
}

void CPU6502::OPCode0x8D(){
    stReg8Abs(&(cpu_context.A));
    n_spend_cycles = n_cycles[0x8D];
}

void CPU6502::OPCode0x8E(){
    stReg8Abs(&(cpu_context.X));
    n_spend_cycles = n_cycles[0x8E];
}

void CPU6502::OPCode0x91(){
    stAIdtIdxY();
    n_spend_cycles = n_cycles[0x91];
}

void CPU6502::OPCode0x94(){
    stReg8ZPReg8(&(cpu_context.Y), &(cpu_context.X));
    n_spend_cycles = n_cycles[0x94];
}

void CPU6502::OPCode0x95(){
    stReg8ZPReg8(&(cpu_context.A), &(cpu_context.X));
    n_spend_cycles = n_cycles[0x95];
}

void CPU6502::OPCode0x96(){
    stReg8ZPReg8(&(cpu_context.X), &(cpu_context.Y));
    n_spend_cycles = n_cycles[0x96];
}

void CPU6502::OPCode0x98(){
    tReg8A(&(cpu_context.Y));
    n_spend_cycles = n_cycles[0x98];
}

void CPU6502::OPCode0x99(){
    stReg8AbsReg8(&(cpu_context.A), &(cpu_context.Y));
    n_spend_cycles = n_cycles[0x99];
}

void CPU6502::OPCode0x9A(){
    tXSP();
    n_spend_cycles = n_cycles[0x9A];
}

void CPU6502::OPCode0x9D(){
    stReg8AbsReg8(&(cpu_context.A), &(cpu_context.X));
    n_spend_cycles = n_cycles[0x9D];
}

void CPU6502::OPCode0xA0(){
    ldReg8Inm(&(cpu_context.Y));
    n_spend_cycles = n_cycles[0xA0];
}

void CPU6502::OPCode0xA2(){
    ldReg8Inm(&(cpu_context.X));
    n_spend_cycles = n_cycles[0xA2];
}

void CPU6502::OPCode0xA1(){
    ldAIdxIdtX();
    n_spend_cycles = n_cycles[0xA1];
}

void CPU6502::OPCode0xA4(){
    ldReg8ZP(&(cpu_context.Y));
    n_spend_cycles = n_cycles[0xA4];
}

void CPU6502::OPCode0xA5(){
    ldReg8ZP(&(cpu_context.A));
    n_spend_cycles = n_cycles[0xA5];
}

void CPU6502::OPCode0xA6(){
    ldReg8ZP(&(cpu_context.X));
    n_spend_cycles = n_cycles[0xA6];
}

void CPU6502::OPCode0xA8(){
    tAReg8(&(cpu_context.Y));
    n_spend_cycles = n_cycles[0xA8];
}

void CPU6502::OPCode0xA9(){
    ldReg8Inm(&(cpu_context.A));
    n_spend_cycles = n_cycles[0xA9];
}

void CPU6502::OPCode0xAA(){
    tAReg8(&(cpu_context.X));
    n_spend_cycles = n_cycles[0xAA];
}

void CPU6502::OPCode0xAC(){
    ldReg8Abs(&(cpu_context.Y));
    n_spend_cycles = n_cycles[0xAC];
}

void CPU6502::OPCode0xAD(){
    ldReg8Abs(&(cpu_context.A));
    n_spend_cycles = n_cycles[0xAD];
}

void CPU6502::OPCode0xAE(){
    ldReg8Abs(&(cpu_context.X));
    n_spend_cycles = n_cycles[0xAE];
}

void CPU6502::OPCode0xB1(){
    ldAIdtIdxY();
    n_spend_cycles = n_cycles[0xB1] + static_cast<u8>(page_crossed);
}

void CPU6502::OPCode0xB4(){
    ldReg8ZPReg8(&(cpu_context.Y), &(cpu_context.X));
    n_spend_cycles = n_cycles[0xB4];
}

void CPU6502::OPCode0xB5(){
    ldReg8ZPReg8(&(cpu_context.A), &(cpu_context.X));
    n_spend_cycles = n_cycles[0xB5];
}

void CPU6502::OPCode0xB6(){
    ldReg8ZPReg8(&(cpu_context.X), &(cpu_context.Y));
    n_spend_cycles = n_cycles[0xB6];
}

void CPU6502::OPCode0xB9(){
    ldReg8AbsReg8(&(cpu_context.A), &(cpu_context.Y));
    n_spend_cycles = n_cycles[0xB9] + static_cast<u8>(page_crossed);
}

void CPU6502::OPCode0xBA(){
    tSPX();
    n_spend_cycles = n_cycles[0xBA];
}

void CPU6502::OPCode0xBC(){
    ldReg8AbsReg8(&(cpu_context.Y), &(cpu_context.X));
    n_spend_cycles = n_cycles[0xBC] + static_cast<u8>(page_crossed);
}

void CPU6502::OPCode0xBD(){
    ldReg8AbsReg8(&(cpu_context.A), &(cpu_context.X));
    n_spend_cycles = n_cycles[0xBD] + static_cast<u8>(page_crossed);
}

void CPU6502::OPCode0xBE(){
    ldReg8AbsReg8(&(cpu_context.X), &(cpu_context.Y));
    n_spend_cycles = n_cycles[0xBE] + static_cast<u8>(page_crossed);
}

