#pragma once
#include "../QuarkEngine/Header/EngineApp.h"
#include <imgui.h>
#include <PathUtils.h>
#include "MenuScene.h"
class GameApp : public EngineApp
{
public:
   

    void OnStart() override
    {
        engine->getSceneManager().SetEngine(engine);
        engine->getSceneManager().ChangeScene(std::make_unique<MenuScene>());
    }

    void OnUpdate(float dt) override { engine->getSceneManager().Update(dt); }
    void OnRender() override { engine->getSceneManager().Render(); }
    void OnImGuiRender() override { engine->getSceneManager().ImGuiRender(); }
};




