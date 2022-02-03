#include "emulator.h"

Emulator::Emulator(){
    curr_state = EmulatorStates::INITIALIZATION;
    memory_mapper = new MemoryMapper();
    cartridge = memory_mapper->peripherals->cartridge;
    cpu = new CPU6502(memory_mapper);
    emu_gui = new EmuGui(&curr_state, memory_mapper->peripherals, &cpu->cpu_context);
    renderer = new Renderer(emu_gui);
}

Emulator::~Emulator(){
    clearPointer(emu_gui);
    clearPointer(renderer);
    clearPointer(memory_mapper);
    clearPointer(cpu);
    cartridge = nullptr;
}

void Emulator::emulate(){
    SDL_Event event;
    cpu->init();
    renderer->init();
    curr_state = EmulatorStates::PAUSED;
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
        case EmulatorStates::RUNNING:
            break;
        case EmulatorStates::RUNNING_STEP:
            cpu->run();
            curr_state = EmulatorStates::PAUSED;
            break;
        case EmulatorStates::LOADING_ROM:
            cpu->reset();
            if(!cartridge->init(emu_gui->getRomPath())){
                std::cout << "Invalid File" << std::endl;
                curr_state = EmulatorStates::ERROR;
            }else{
                curr_state = EmulatorStates::PAUSED;
            }
            break;
        case EmulatorStates::ERROR:
            break;
        default:
            break;
        }
        renderer->render();
    }
}