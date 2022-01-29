#include "emulator.h"

Emulator::Emulator(){
    curr_state = EmulatorStates::INITIALIZATION;
    emu_gui = new EmuGui(&curr_state);
    renderer = new Renderer(emu_gui);
}

Emulator::~Emulator(){
    clearPointer(emu_gui);
    clearPointer(renderer);
}

void Emulator::emulate(){
    SDL_Event event;
    while(curr_state != EmulatorStates::FINISHED){
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        while (SDL_PollEvent(&event)){
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                curr_state = EmulatorStates::FINISHED;
        }
        switch(curr_state){
        case EmulatorStates::INITIALIZATION:
            renderer->init();
            curr_state = EmulatorStates::RUNNING;
            break;
        case EmulatorStates::RUNNING:
            renderer->render();
            break;
        case EmulatorStates::LOADING_ROM:
            std::cout << (emu_gui->getRomPath()).c_str() << std::endl;
            renderer->render();
            curr_state = EmulatorStates::RUNNING;
            break;
        default:
            break;
        }
    }
}