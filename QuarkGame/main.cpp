#pragma once
#include "EngineCore.h"


int main(int argc, char** argv) {
    EngineCore engine;

    if (!engine.Initialize()) {
        // handle initialization failure
        return -1;
    }

    engine.RunMainLoop();

    engine.Shutdown();
    return 0;
}