#ifndef CARTRIDGE_H
#define CARTRIDGE_H
#include "data_types.h"
#include "util.h"
#include "states_flags.h"
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>

namespace HeaderFormat{
    enum HeaderFormat{
        NONE, INES, NES20
    };    
}

class Cartridge{
    private:
        std::string rom_path;
        word n_16k_rom_banks;
        word n_8k_vrom_banks;
        byte *header;
        int headerType;
    public:
        const word ROM_SZ = 0x4000;
        const word VROM_SZ = 0x2000;
        byte *rom_l_bank, *rom_u_bank;
    public:
        Cartridge();
        ~Cartridge();
        bool init(std::string rom_path);
        void updateBank(bit bank, u16 n_page);
        byte getN16KRomBanks();
        byte getN8KVRomBanks();
        byte getMapper();
};
#endif