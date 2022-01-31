#ifndef GUI_H
#define GUI_H
#include "states_flags.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileBrowser.h"
#include "imgui_internal.h"
#include "../UI/MemoryEditor/imgui_memory_editor.h"
#include "util.h"
#include "cartridge.h"
#include "memory_map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

class EmuGui{
    private:
        int *emu_state;
        imgui_addons::ImGuiFileBrowser *file_dialog;
        MemoryEditor *mem_edit;
        Peripherals *peripherals;
        int file_dialog_flags, memory_dump_state;
    public:
        EmuGui(int *emu_state, Peripherals *peripherals);
        ~EmuGui();
        void init();
        void renderFileDialog();
        void renderMemEditor();
        void render();
        std::string getRomPath();
};
#endif