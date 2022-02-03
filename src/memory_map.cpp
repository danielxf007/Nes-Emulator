#include "memory_map.h"

NRom256::NRom256(Peripherals *peripherals){
    this->peripherals = peripherals;
}


NRom256::~NRom256(){
    peripherals = nullptr;
}

byte NRom256::read(word addr){
    byte aux;
    addr_space.value = addr;
    if(addr_space.block < 32){
        aux = addr_space.block % 8;
        if(aux == 0x00)
            return peripherals->zero_page[addr_space.n_element];
        if(aux == 0x01)
            return peripherals->stack[addr_space.n_element];
        return peripherals->ram[addr_space.n_element + addr_space.block_sz*(aux-2)];
    }
    if(addr_space.block < 64)
        return peripherals->io_regs0[addr_space.n_element % 8];
    if(addr_space.block < 96){
        aux = addr_space.block % 32;
        if(aux == 0x00 && addr_space.n_element < 0x20)
            return peripherals->io_regs1[addr_space.n_element];
        return peripherals->expansion_rom[addr_space.n_element + addr_space.block_sz*aux];
    }
    if(addr_space.block < 128){
        aux = addr_space.block % 32;
        return peripherals->sram[addr_space.n_element + addr_space.block_sz*aux];
    }
    aux = addr_space.block % 64;
    if(addr_space.block < 192)
        return peripherals->cartridge->rom_l_bank[addr_space.n_element + addr_space.block_sz*aux];
    return peripherals->cartridge->rom_u_bank[addr_space.n_element + addr_space.block_sz*aux];
}

void NRom256::write(word addr, byte value){
    byte aux;
    addr_space.value = addr;
    if(addr_space.block < 32){
        aux = addr_space.block % 8;
        if(aux == 0x00)
            peripherals->zero_page[addr_space.n_element] = value;
        else if(aux == 0x01)
            peripherals->stack[addr_space.n_element] = value;
        else 
            peripherals->ram[addr_space.n_element + addr_space.block_sz*(aux-2)] = value;
    }else if(addr_space.block < 64)
        peripherals->io_regs0[addr_space.n_element % 8] = value;
    else if(addr_space.block < 96){
        aux = addr_space.block % 32;
        if(aux == 0x00 && addr_space.n_element < 0x20)
            peripherals->io_regs1[addr_space.n_element] = value;
        else
            peripherals->expansion_rom[addr_space.n_element + addr_space.block_sz*aux] = value;
    }else if(addr_space.block < 128){
        aux = addr_space.block % 32;
        peripherals->sram[addr_space.n_element + addr_space.block_sz*aux] = value;
    }else{
        aux = addr_space.block % 64;
        if(addr_space.block < 192)
            peripherals->cartridge->rom_l_bank[addr_space.n_element + addr_space.block_sz*aux] = value;
        else
            peripherals->cartridge->rom_u_bank[addr_space.n_element + addr_space.block_sz*aux] = value;
    }
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
