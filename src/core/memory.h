#include "data_types.h"

namespace NROM256Limits{
    word zero_page, stack, ram, mirror0, io_regs0,
    mirror1, io_regs1, exp_rom, sram, rom0, rom1;   
}

namespace MemoryMappings{
    enum {NROM256};
}

class Memory{
    private:
        byte *mem;
        byte memory_mapping;
    
    public:
        Memory();
        ~Memory();
        byte *getMem();
        void read(word addr, byte &buffer);
        void read(word addr, word &buffer);
        void write(word addr, byte value);
        void write(word addr, word value);
        inline void readNROMmapping(word addr, byte &buffer);
        inline void readNROMmapping(word addr, word &buffer);
        inline void writeNROMmapping(word addr, byte value);
        inline void writeROMmapping(word addr, word value);
};

inline void Memory::readNROMmapping(word addr, byte &buffer){
    buffer = mem[addr];
}

inline void Memory::readNROMmapping(word addr, word &buffer){
    buffer = (static_cast<word>(mem[addr+1]) << 8) | static_cast<word>(mem[addr]);
}

inline void Memory::writeNROMmapping(word addr, byte value){
    mem[addr] = value;
}