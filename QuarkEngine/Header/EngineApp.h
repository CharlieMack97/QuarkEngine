#pragma once
#include <vector>

class EngineCore;
class GameObject;

class EngineApp
{
public:
    EngineApp();
    virtual ~EngineApp();
    void Initialize(EngineCore* core);

    virtual void OnStart();
    virtual void OnUpdate(float dt);
    virtual void OnImGuiRender() {};
    virtual void OnRender();
    virtual void OnShutdown();

protected:
    EngineCore* engine = nullptr;
};

