#pragma once
#include <vector>

class EngineCore;
class GameObject;

class EngineApp
{
public:
    EngineApp();
    virtual ~EngineApp();

    // Called by EngineCore after initialization
    void Initialize(EngineCore* core);

    // Game lifecycle hooks
    virtual void OnStart();
    virtual void OnUpdate(float dt);
    virtual void OnRender();
    virtual void OnShutdown();

protected:
    EngineCore* engine = nullptr;
};

