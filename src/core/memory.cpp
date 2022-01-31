#include "memory.h"

Memory::Memory(){
    mem = new byte[0x10000];
    memory_mapping = MemoryMappings::NROM256;
}

Memory::~Memory(){
    delete mem;
    mem = nullptr;
}

byte* Memory::getMem(){
    return mem;
}
void Memory::read(word addr, byte &buffer){
    switch(memory_mapping){
    case MemoryMappings::NROM256:
        readNROMmapping(addr, buffer);
        break;
    default:
        break;
    }
}

void Memory::read(word addr, word &buffer){
    switch(memory_mapping){
    case MemoryMappings::NROM256:
        readNROMmapping(addr, buffer);
        break;
    default:
        break;
    }
}

void Memory:: write(word addr, byte value){
    switch(memory_mapping){
    case MemoryMappings::NROM256:
        writeNROMmapping(addr, value);
        break;
    default:
        break;
    }    
}

void Memory:: write(word addr, word value){
    switch(memory_mapping){
    case MemoryMappings::NROM256:
        writeNROMmapping(addr, value);
        break;
    default:
        break;
    }    
}