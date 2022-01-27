#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileBrowser.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

class Graphicator{
    private:
        SDL_Window *window;
        SDL_Surface *window_surface;
        const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        imgui_addons::ImGuiFileBrowser file_dialog;
        ImGuiIO io;
    public:
        Graphicator(SDL_Window *window);
        ~Graphicator();
        void render();
};

#endif