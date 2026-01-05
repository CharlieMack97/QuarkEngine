#pragma once
#include "EngineCore.h"
#include "GameApp.h"
int main()
{
    EngineCore engine;
    GameApp game;

    engine.Initialize(&game);
    engine.RunMainLoop();
    engine.Shutdown();

    return 0;
}
