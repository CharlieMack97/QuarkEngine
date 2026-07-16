#pragma once
#include <memory>
#include "Scene.h"

class SceneManager
{
public:
    void SetEngine(EngineCore* eng) 
    {
        engine = eng; 
    }
    void ChangeScene(std::unique_ptr<Scene> newScene)
    {
        pendingScene = std::move(newScene);
    }

    void Update(float dt)
    {
        if (pendingScene)
        {
            if (currentScene) currentScene->OnExit();
            currentScene = std::move(pendingScene);
            currentScene->engine = engine;
            currentScene->OnEnter();
        }
        if (currentScene) currentScene->OnUpdate(dt);
    }

    void Render() { if (currentScene) currentScene->OnRender(); }
    void ImGuiRender() { if (currentScene) currentScene->OnImGuiRender(); }

private:
    EngineCore* engine = nullptr;
    std::unique_ptr<Scene> currentScene;
    std::unique_ptr<Scene> pendingScene;
};