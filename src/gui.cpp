#include "gui.h"

EmuGui::EmuGui(int *emu_state){
    this->emu_state = emu_state;
    file_dialog = nullptr;
    file_dialog_flags = 0;
}

EmuGui::~EmuGui(){
    clearPointer(file_dialog);
}

void EmuGui::init(){
    file_dialog = new imgui_addons::ImGuiFileBrowser();
}

void EmuGui::renderFileDialog(){

    if(ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            if (ImGui::MenuItem("Open", NULL)){
                file_dialog_flags |= FileDialogFlags::OPEN;
            }else{
                file_dialog_flags &= (~FileDialogFlags::OPEN);
            }
            if (ImGui::MenuItem("Save", NULL)){
                file_dialog_flags |= FileDialogFlags::SAVE;
            }else{
                file_dialog_flags &= (~FileDialogFlags::SAVE);
            }
            
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
    if(file_dialog->showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".nes")){
       *emu_state = EmulatorStates::LOADING_ROM;
       file_dialog_flags &= (~FileDialogFlags::OPEN);
    }
    if(file_dialog->showFileDialog("Save File", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), ".png,.jpg,.bmp")){
    }    
}

void EmuGui::render(){
    renderFileDialog();
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