#include "graphics.h"
#include "imgui_internal.h"
#include <cmath>

Graphicator::Graphicator(SDL_Window *window){
    this->window = window;
    this->window_surface = SDL_GetWindowSurface(window);
    io  = ImGui::GetIO(); (void)io;
}

Graphicator::~Graphicator(){
    window_surface = NULL;
}

void Graphicator::render(){
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        bool open = false, save = false;
        if(ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                if (ImGui::MenuItem("Open", NULL))
                    open = true;
            if (ImGui::MenuItem("Save", NULL))
                    save = true;
                
            ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        
        //Remember the name to ImGui::OpenPopup() and showFileDialog() must be same...
        if(open)
            ImGui::OpenPopup("Open File");
        if(save)
            ImGui::OpenPopup("Save File");
            
        /* Optional third parameter. Support opening only compressed rar/zip files. 
        * Opening any other file will show error, return false and won't close the dialog.
        */
        if(file_dialog.showFileDialog("Open File", imgui_addons::ImGuiFileBrowser::DialogMode::OPEN, ImVec2(700, 310), ".rar,.zip,.7z"))
        {
            std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
            std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
        }
        if(file_dialog.showFileDialog("Save File", imgui_addons::ImGuiFileBrowser::DialogMode::SAVE, ImVec2(700, 310), ".png,.jpg,.bmp"))
        {
            std::cout << file_dialog.selected_fn << std::endl;      // The name of the selected file or directory in case of Select Directory dialog mode
            std::cout << file_dialog.selected_path << std::endl;    // The absolute path to the selected file
            std::cout << file_dialog.ext << std::endl;              // Access ext separately (For SAVE mode)
            //Do writing of files based on extension here
        }
        ImGui::Begin("Controls");
        ImGui::BeginChild("D");
        ImGui::BeginTabBar("Bar", 0);
            ImGui::Button("one", ImVec2(50, 50));
        ImGui::EndTabBar();
        ImGui::EndChild();
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
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
}