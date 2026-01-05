#include "EngineApp.h"
#include "EngineCore.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "Header/GameObject.h"

EngineApp::EngineApp() {}
EngineApp::~EngineApp() {}

void EngineApp::Initialize(EngineCore* core)
{
    engine = core;
    OnStart();
}

void EngineApp::OnStart()
{
    // do nothing
}

void EngineApp::OnUpdate(float dt)
{
    //do nothing
}

void EngineApp::OnRender()
{
    // do nothing
}

void EngineApp::OnShutdown()
{
    // do nothing
}

