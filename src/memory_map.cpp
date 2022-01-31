#include "memory_map.h"

NRom256::NRom256(Peripherals *peripherals){
    this->peripherals = peripherals;
}


NRom256::~NRom256(){
    peripherals = nullptr;
}

byte NRom256::read(word addr){
    word aux_addr = addr % 0x800;
    if(aux_addr < 0x100){
        return peripherals->zero_page[aux_addr]; 
    }else if(aux_addr < 0x200){
        return peripherals->stack[aux_addr];
    }else if(aux_addr < 0x800){
        return peripherals->ram[aux_addr];
    }
    if(addr < 0x4000){
        aux_addr = (addr - 0x2000)%8;
        return peripherals->io_regs0[aux_addr];
    }else if(addr < 0x4020){
        aux_addr = (addr - 0x4000);
        return peripherals->io_regs1[aux_addr];
    }
    if(addr < 0x6000){
        aux_addr = addr - 0x4020;
        return peripherals->expansion_rom[aux_addr];
    }
    if(addr < 0x8000){
        aux_addr = addr - 0x6000;
        return peripherals->sram[aux_addr];
    }
    if(addr < 0xC000){
        aux_addr = addr - 0x8000;
        return peripherals->cartridge->rom_l_bank[aux_addr];
    }
    aux_addr = addr - 0xC000;
    return peripherals->cartridge->rom_u_bank[aux_addr];
}

void NRom256::write(word addr, byte value){
    word aux_addr = addr % 0x800;
    if(aux_addr < 0x100){
        peripherals->zero_page[aux_addr] = value;
        return; 
    }else if(aux_addr < 0x200){
        peripherals->stack[aux_addr] = value;
        return;
    }else if(aux_addr < 0x800){
        peripherals->ram[aux_addr] = value;
        return;
    }
    if(addr < 0x4000){
        aux_addr = (addr - 0x2000)%8;
        peripherals->io_regs0[aux_addr] = value;
        return;
    }else if(addr < 0x4020){
        aux_addr = (addr - 0x4000);
        peripherals->io_regs1[aux_addr] = value;
        return;
    }
    if(addr < 0x6000){
        aux_addr = addr - 0x4020;
        peripherals->expansion_rom[aux_addr] = value;
        return;
    }
    if(addr < 0x8000){
        aux_addr = addr - 0x6000;
        peripherals->sram[aux_addr] = value;
        return;
    }
    if(addr < 0xC000){
        aux_addr = addr - 0x8000;
        peripherals->cartridge->rom_l_bank[aux_addr] = value;
    }
    aux_addr = addr - 0xC000;
    peripherals->cartridge->rom_u_bank[aux_addr] = value;
}

//
MemoryMapper::MemoryMapper(){
    mapping_type = MemoryMappers::NROM256;
    peripherals = new Peripherals;
    peripherals->cartridge = new Cartridge();
    n_rom_256 = new NRom256(peripherals);
}

MemoryMapper::~MemoryMapper(){
    clearPointer(peripherals->cartridge);
    clearPointer(n_rom_256);
    clearPointer(peripherals);
}

byte MemoryMapper::read(word addr){
    switch(mapping_type){
    case MemoryMappers::NROM256:
        return n_rom_256->read(addr);
    default:
        break;
    }
    return 0;
}

void MemoryMapper::write(word addr, byte value){
    switch(mapping_type){
    case MemoryMappers::NROM256:
        n_rom_256->write(addr, value);
        break;
    default:
        break;
    }
}
