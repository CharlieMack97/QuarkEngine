#pragma once
#include "SDL3/SDL.h"
#include <iostream>
#include "SDL3/SDL_main.h"
#include "InterfaceRenderer.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include <bx/uint32_t.h>
#include "Header/GameObject.h"
#include <../Box2D/include/box2d/box2d.h>
#include "InputManager.h"
class EngineApp;
class EngineCore {
public:
    EngineCore();
    ~EngineCore();

    bool Initialize(EngineApp* app);
    void RendererFrame();
    void RunMainLoop();
    void Shutdown();
    void CreateGround(float screenWidth, float screenHeight, float PPM);
    TextureManager* getTextureManager();
    b2WorldId getWorldId() { return physicsWorld; };
    InputManager& getMouseInput() { return mouseInput; };

private:
    EngineApp* appLayer = nullptr;
    std::unique_ptr<TimeManager> timeManager;
    bool running = false;
    std::unique_ptr<InterfaceRenderer> rendererI;
    std::unique_ptr <TextureManager> txtManager;
    b2WorldId physicsWorld = b2_nullWorldId;
    InputManager mouseInput;
    
};



