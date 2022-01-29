#include "emulator.h"

int main(int argc, char *args[]){
    Emulator *emulator = new Emulator();
    emulator->emulate();
    delete emulator;
    emulator = nullptr;
    return EXIT_SUCCESS;
}