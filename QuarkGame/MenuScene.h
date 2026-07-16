#pragma once
#include "Scene.h"
#include "../QuarkEngine/Header/EngineCore.h"
#include "GameScene.h"

class MenuScene : public Scene
{
public:
    void OnImGuiRender() override
    {
        ImGui::SetNextWindowPos(ImVec2(700, 400), ImGuiCond_Always);
        ImGui::Begin("Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::Text("Brick Breaker");
        if (ImGui::Button("Start Game"))
        {
            engine->getSceneManager().ChangeScene(std::make_unique<GameScene>());
        }
        ImGui::End();
    }
};