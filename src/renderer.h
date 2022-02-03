#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ImGuiFileBrowser.h"
#include "imgui_internal.h"
#include "gui.h"
#include "util.h"
#include "shader.h"
#include <stdio.h>


class Renderer{
    private:
        Shader *shader;
        const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        const char* glsl_version = "#version 130";
        unsigned int VBO, VAO;
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