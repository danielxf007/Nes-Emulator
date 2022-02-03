#ifndef STATES_H
#define STATES_H

namespace EmulatorStates{
    enum{
        INITIALIZATION, PAUSED, RUNNING, RUNNING_STEP, LOADING_ROM, FINISHED, ERROR
    };

    enum{

    };
}

namespace FileDialogFlags{
    enum{
        OPEN = 0x1, SAVE = 0x20
    };
}

namespace MemoryMappers{
    enum{
        NROM256
    };
}
#endif