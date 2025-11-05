#pragma once
#include "SDL3/SDL.h"
#include <iostream>
#include "SDL3/SDL_main.h"
#include "InterfaceRenderer.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include <bx/uint32_t.h>
#include "Header/GameObject.h"

class EngineCore {
public:
    EngineCore();
    ~EngineCore();

    bool Initialize();
    void RendererFrame();
    void RunMainLoop();
    void Shutdown();
    TextureManager* getTextureManager();
private:
   
    std::unique_ptr<TimeManager> timeManager;
    bool running = false;
    std::unique_ptr<InterfaceRenderer> rendererI;
    std::unique_ptr <TextureManager> txtManager;
    std::vector<GameObject*> gameObjects;
    //testing
    GameObject* gameObj;
};



