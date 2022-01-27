#include "emulator.h"

int main(int argc, char *args[]){
    Emulator *emulator = new Emulator();
    emulator->emulate();
    delete emulator;
    return EXIT_SUCCESS;
}