#include "cpu.h"

CPU6502::CPU6502(){
    cpu_context.A = 0;
    cpu_context.X = 0;
    cpu_context.Y = 0;
    cpu_context.P = 0x20;
    cpu_context.SP = 0xFF;
}

void CPU6502::reset(){
    cpu_context.A = 0;
    cpu_context.X = 0;
    cpu_context.Y = 0;
    cpu_context.P = 0x20;
    cpu_context.SP = 0xFF;
}