#include "states_flags.h"
#include "renderer.h"
#include "gui.h"
#include <iostream>

class Emulator{
    private:
        EmuGui *emu_gui;
        Renderer *renderer;
        int curr_state;
    public:
        Emulator();
        ~Emulator();
        void emulate();
};