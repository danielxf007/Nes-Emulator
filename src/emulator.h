#include "states.h"
#include "renderer.h"

class Emulator{
    private:
        Renderer *renderer;
        int curr_state;
    public:
        Emulator();
        ~Emulator();
        void emulate();
};