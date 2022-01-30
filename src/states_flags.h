#ifndef STATES_H
#define STATES_H

namespace EmulatorStates{
    enum {
        INITIALIZATION, RUNNING, PAUSED, LOADING_ROM, SETING_UP_SYSTEM, FINISHED 
    };
}

namespace FileDialogFlags{
    enum{
        OPEN = 0x1, SAVE = 0x20
    };
}
#endif