#include "states_flags.h"
#include "renderer.h"
#include "gui.h"
#include "cartridge.h"
#include "memory_map.h"
#include "cpu.h"
#include <iostream>

class Emulator{
    private:
        EmuGui *emu_gui;
        Renderer *renderer;
        MemoryMapper *memory_mapper;
        Cartridge *cartridge;
        CPU6502 *cpu;
        int curr_state;
    public:
        Emulator();
        ~Emulator();
        void emulate();
};