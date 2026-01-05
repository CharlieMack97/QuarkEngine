#include "EngineCore.h"
#include "Renderer.h"
#include "TimeManager.h"
#include "EngineApp.h"
#include <SDL3/SDL.h>
#include "Components/TransformComp.h"
#include "Components/RendererComp.h"
#include <bgfx/bgfx.h>
static uint32_t frameNum = 0;
EngineCore::EngineCore() {
	
}

EngineCore::~EngineCore() {
	
}

bool EngineCore::Initialize(EngineApp* app)
{

	
	//initilising systems
	appLayer = app;

	timeManager = std::make_unique<TimeManager>();
	timeManager->init();

	rendererI = std::make_unique<Renderer>();
	rendererI->Init();

	txtManager = std::make_unique<TextureManager>();
	//phys
	b2WorldDef worldDef = b2DefaultWorldDef();
	worldDef.gravity = { 0.0f, 10.f }; 
	physicsWorld = b2CreateWorld(&worldDef);

	// Let the game layer initialize itself
	if (appLayer)
		appLayer->Initialize(this);

	running = true;
	return true;
	
}

void EngineCore::RendererFrame()
{
	if (!rendererI)
		return;

	rendererI->BeginFrame();

	if (appLayer)
	{
		appLayer->OnRender();
	}
	rendererI->EndFrame();
}
void EngineCore::RunMainLoop() {
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) 
		{
			SDL_PumpEvents();
			mouseInput.Update();
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		SDL_Delay(16);

		timeManager->update(); 
		float dt = timeManager->getDeltaTime();
		b2World_Step(physicsWorld, dt, 4);
		CreateGround(2200, 2300, 100);
		if (appLayer)
			appLayer->OnUpdate(dt);

		RendererFrame();
	}

	if (appLayer)
		appLayer->OnShutdown();
}

void EngineCore::Shutdown() {
	rendererI->Shutdown();
	if (txtManager)
	{
		txtManager->shutdown();
	}
	SDL_Quit();
}

TextureManager* EngineCore::getTextureManager()
{
	return txtManager.get();
}

void EngineCore::CreateGround(float screenWidth, float screenHeight, float PPM)
{
	if (!b2World_IsValid(physicsWorld)) return;

	b2BodyDef groundDef = b2DefaultBodyDef();
	groundDef.type = b2_staticBody;

	
	groundDef.position = { (screenWidth / 2.0f) / PPM, 0.25f };

	b2BodyId ground = b2CreateBody(physicsWorld, &groundDef);

	
	b2Polygon box = b2MakeBox((screenWidth / 2.0f) / PPM, 0.5f);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	b2CreatePolygonShape(ground, &shapeDef, &box);
}