#pragma once
#include "SDL3/SDL.h"
#include <iostream>
#include "SDL3/SDL_main.h"
#include "bgfx/bgfx.h"
class EngineCore {
public:
    EngineCore();
    ~EngineCore();

    bool Initialize();
    void RunMainLoop();
    void Shutdown();
private:
    SDL_Window* window = nullptr;
    bool running = false;
};



