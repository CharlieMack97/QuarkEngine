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
    
}

void EngineApp::OnUpdate(float dt)
{
   
}

void EngineApp::OnRender()
{
  
}

void EngineApp::OnShutdown()
{
   
}

