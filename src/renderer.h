#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileBrowser.h"
#include "imgui_internal.h"
#include "gui.h"
#include "util.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

class Renderer{
    private:
        const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        const char* glsl_version = "#version 130";
        SDL_Window *window;
        SDL_GLContext gl_context;
        EmuGui *emu_gui;
        ImGuiIO io;
    public:
        Renderer(EmuGui *emu_gui);
        ~Renderer();
        void init();
        void render();
};

#endif