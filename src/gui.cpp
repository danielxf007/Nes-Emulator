#include "gui.h"

EmuGui::EmuGui(int *emu_state, Peripherals *peripherals, CPUContext *cpu_context){
    this->emu_state = emu_state;
    this->peripherals = peripherals;
    this->cpu_context = cpu_context;
    file_dialog = nullptr;
    mem_edit = nullptr;
    stack_dump = nullptr;
    file_dialog_flags = 0;
}

EmuGui::~EmuGui(){
    clearPointer(file_dialog);
    clearPointer(mem_edit);
    clearPointer(stack_dump);
    emu_state = nullptr;
    peripherals = nullptr;
    cpu_context = nullptr;
}

void EmuGui::init(){
    file_dialog = new imgui_addons::ImGuiFileBrowser();
    mem_edit = new MemoryEditor();
    stack_dump = new MemoryEditor();
    stack_dump->Cols = 1;
}

void EmuGui::renderFileDialog(){
    file_dialog_flags = 0;
    if(ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            if (ImGui::MenuItem("Open", NULL))
                file_dialog_flags |= FileDialogFlags::OPEN;
            if (ImGui::MenuItem("Save", NULL))
                file_dialog_flags |= FileDialogFlags::SAVE;
                
        ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    //Remember the name to ImGui::OpenPopup() and showFileDialog() must be same...
    if(file_dialog_flags & FileDialogFlags::OPEN)
        ImGui::OpenPopup("Open File");
    if(file_dialog_flags & FileDialogFlags::SAVE)
        ImGui::OpenPopup("Save File");
        
    /* Optional third parameter. Support opening only compressed rar/zip files. 
    * Opening any other file will show error, return false and won't close the dialog.
    */
    if(file_dialog->showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".nes, .bin")){
       *emu_state = EmulatorStates::LOADING_ROM;
    }
    if(file_dialog->showFileDialog("Save File", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), ".png,.jpg,.bmp")){
    }    
}

void EmuGui::renderMemEditor(){
    if(ImGui::Begin("Memory Dumps")){
        if(ImGui::BeginTabBar("##memory_dumps", ImGuiTabBarFlags_None)){
            if(ImGui::BeginTabItem("Zero Page")){
                mem_edit->DrawContents(peripherals->zero_page, sizeof(peripherals->zero_page), 0);
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("RAM")){
                mem_edit->DrawContents(peripherals->ram, sizeof(peripherals->ram), 0);
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Expansion Rom")){
                mem_edit->DrawContents(peripherals->expansion_rom, sizeof(peripherals->expansion_rom), 0);
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("SRAM")){
                mem_edit->DrawContents(peripherals->sram, sizeof(peripherals->sram), 0);
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Lower ROM")){
                mem_edit->DrawContents(peripherals->cartridge->rom_l_bank, peripherals->cartridge->ROM_SZ, 0);
                ImGui::EndTabItem();
            }
            if(ImGui::BeginTabItem("Upper ROM")){
                mem_edit->DrawContents(peripherals->cartridge->rom_u_bank, peripherals->cartridge->ROM_SZ, 0);
                ImGui::EndTabItem();
            }
            ImGui::EndTabBar();
        ImGui::End();
        }
    }
}

void EmuGui::renderStackDump(){
    stack_dump->DrawWindow("Stack Dump", peripherals->stack, sizeof(peripherals->stack));
}

void EmuGui::renderCPURegisters(){
     ImGui::SetNextWindowSize(ImVec2(200, 260));
    if(ImGui::Begin("CPU Registers")){
        if (ImGui::BeginTable("Registers", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)){
            ImGui::TableSetupColumn("Register");
            ImGui::TableSetupColumn("Value");
            ImGui::TableHeadersRow();
            renderRegister8("A", (cpu_context->A).value);
            renderRegister8("X", (cpu_context->X).value);
            renderRegister8("Y", (cpu_context->Y).value);
            renderRegister8("SP", (cpu_context->SP).value);
            renderRegister16("PC", cpu_context->PC);
            renderFlag("N", (cpu_context->P).N);
            renderFlag("V", (cpu_context->P).V);
            renderFlag("B", (cpu_context->P).B);
            renderFlag("D", (cpu_context->P).D);
            renderFlag("I", (cpu_context->P).I);
            renderFlag("Z", (cpu_context->P).Z);
            renderFlag("C", (cpu_context->P).C);
            ImGui::EndTable();
        }        
        ImGui::End();
    }else
        ImGui::End();
}

void EmuGui::renderControls(){
    if(ImGui::Begin("Controls")){
        if(ImGui::Button("Play", ImVec2(50, 25))){
            *emu_state = EmulatorStates::RUNNING;
        }
        ImGui::SameLine();
        if(ImGui::Button("Pause", ImVec2(50, 25))){
            *emu_state = EmulatorStates::PAUSED;
        }
        ImGui::SameLine();
        if(ImGui::Button("Step", ImVec2(50, 25))){
            *emu_state = EmulatorStates::RUNNING_STEP;
        }
        ImGui::End();
    }else
        ImGui::End();
}

void EmuGui::render(){
    renderFileDialog();
    renderMemEditor();
    renderStackDump();
    renderCPURegisters();
    renderControls();
    /*
    ImGui::Begin("Controls");
        ImGui::Button("one", ImVec2(50, 50));
    ImGui::End();

    ImGui::Begin("Tables");
    
    if (ImGui::BeginTable("table_padding", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("Register");
        ImGui::TableSetupColumn("Value");
        ImGui::TableHeadersRow();

        for (int row = 0; row < 2; row++)
        {
            ImGui::TableNextRow();
            for (int column = 0; column < 2; column++)
            {
                ImGui::TableSetColumnIndex(column);
                ImGui::Text("Hello %d,%d", column, row);
            }
        }
        ImGui::EndTable();
    }
    ImGui::End();
    */  
}

std::string EmuGui::getRomPath() {
    return file_dialog->selected_path;
}