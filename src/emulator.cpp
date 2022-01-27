#include "emulator.h"

Emulator::Emulator(){
    renderer = new Renderer();
    curr_state = EmulatorStates::PAUSED;
}

Emulator::~Emulator(){
    delete renderer;
}

void Emulator::emulate(){
    bool done = false;
    SDL_Event event;
    while (!done){
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        while (SDL_PollEvent(&event)){
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }
        renderer->render();
    }
}