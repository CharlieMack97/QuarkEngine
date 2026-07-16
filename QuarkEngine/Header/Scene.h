#pragma once

class EngineCore; 

class Scene
{
public:
    virtual ~Scene() = default;

    virtual void OnEnter() {} 
    virtual void OnExit() {}    
    virtual void OnUpdate(float dt) {}
    virtual void OnRender() {}
    virtual void OnImGuiRender() {}

protected:
    EngineCore* engine = nullptr;
    friend class SceneManager;
};