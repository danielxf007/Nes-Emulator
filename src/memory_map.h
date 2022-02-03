#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H
#include "data_types.h"
#include "states_flags.h"
#include "cartridge.h"

struct Peripherals{
    byte zero_page[0x100], stack[0x100], ram[0x600], io_regs0[8], io_regs1[0x20];
    byte expansion_rom[0x1FE0], sram[0x2000];
    Cartridge *cartridge;
};

typedef struct{
    const word block_sz = 256;
    union{
        word value;
        struct {
            byte n_element, block;
        };
    };
}AddrSpace;

class NRom256{

    private:
        AddrSpace addr_space;
        Peripherals *peripherals;
    
    public:
        NRom256(Peripherals *peripherals);
        ~NRom256();
        byte read(word addr);
        void write(word addr, byte value);
};

class MemoryMapper{
    private:
        NRom256 *n_rom_256;
    public:
        Peripherals *peripherals;
        int mapping_type;
    public:
        MemoryMapper();
        ~MemoryMapper();
        byte read(word addr);
        void write(word addr, byte value);    
};
#endif