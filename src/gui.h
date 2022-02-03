#ifndef GUI_H
#define GUI_H
#include "states_flags.h"
#include "imgui.h"
#include "ImGuiFileBrowser.h"
#include "imgui_internal.h"
#include "../UI/MemoryEditor/imgui_memory_editor.h"
#include "util.h"
#include "cartridge.h"
#include "memory_map.h"
#include "cpu.h"
#include "data_types.h"
#include <iostream>

class EmuGui{
    private:
        int *emu_state;
        imgui_addons::ImGuiFileBrowser *file_dialog;
        MemoryEditor *mem_edit, *stack_dump;
        Peripherals *peripherals;
        int file_dialog_flags, memory_dump_state;
        CPUContext *cpu_context;
    public:
        EmuGui(int *emu_state, Peripherals *peripherals, CPUContext *cpu_context);
        ~EmuGui();
        void init();
        void renderFileDialog();
        void renderMemEditor();
        void renderStackDump();
        inline void renderRegister8(const char *reg_name, byte value);
        inline void renderRegister16(const char *reg_name, word value);
        inline void renderFlag(const char *reg_name, bit value);
        void renderCPURegisters();
        void renderControls();
        void render();
        std::string getRomPath();
};

inline void EmuGui::renderRegister8(const char *reg_name, byte value){
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text(reg_name);
    ImGui::TableSetColumnIndex(1);
    ImGui::Text("0x%02X", value);    
}

inline void EmuGui::renderRegister16(const char *reg_name, word value){
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text(reg_name);
    ImGui::TableSetColumnIndex(1);
    ImGui::Text("0x%04X", value);    
}

inline void EmuGui::renderFlag(const char *reg_name, bit value){
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Text(reg_name);
    ImGui::TableSetColumnIndex(1);
    ImGui::Text("0x%01X", value);    
}

#endif