#include "cartridge.h"

Cartridge::Cartridge(){
    header = new byte[16];
    rom_l_bank = new byte[ROM_SZ];
    rom_u_bank = new byte[ROM_SZ];
    headerType = HeaderFormat::NONE;
}

Cartridge::~Cartridge(){
    clearPointer(header);
    clearPointer(rom_l_bank);
    clearPointer(rom_u_bank);
}

bool Cartridge::init(std::string rom_path){
    std::FILE *file;
    headerType = HeaderFormat::NONE;
    this->rom_path = rom_path;
    file = std::fopen(rom_path.c_str(), "rb");
    if(file){
        std::fread(header, 1, 16, file);
        if (header[0]=='N' && header[1]=='E' && header[2]=='S' && header[3]==0x1A)
            headerType = HeaderFormat::INES;
        if (headerType == HeaderFormat::INES && (header[7]&0x0C)==0x08)
            headerType = HeaderFormat::NES20;
        if(headerType != HeaderFormat::NONE){
            updateBank(0, 0);
            if(getMapper() == MemoryMappers::NROM256){
                updateBank(1, 0);
            }else{
                updateBank(1, 1);
            }
        }
        std::fclose(file);
    }
    return headerType != HeaderFormat::NONE;
}

void Cartridge::updateBank(bit bank, u16 n_page){
    std::FILE *file;
    file = std::fopen(rom_path.c_str(), "rb");
    if(file){
        std::fseek(file, 16 + 512*(getBit(header[6], 3)) + ROM_SZ*n_page, SEEK_SET);
        std::fread(bank == 0 ? rom_l_bank : rom_u_bank, 1, ROM_SZ, file);
        std::fclose(file);
    }
}


byte Cartridge::getN16KRomBanks(){
    return header[4];
}

byte Cartridge::getN8KVRomBanks(){
    return header[5];
}

byte Cartridge::getMapper(){
    return (getNibble(header[7], 1) << 4) | getNibble(header[6], 1);
}