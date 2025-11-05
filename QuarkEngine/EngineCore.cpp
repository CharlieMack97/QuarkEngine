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

bool EngineCore::Initialize() 
{

	
	//initilising systems
	timeManager = std::make_unique<TimeManager>();
	timeManager->init();

	rendererI= std::make_unique<Renderer>();
	rendererI->Init();
	txtManager = std::make_unique<TextureManager>();




	//testing obj
	gameObj = new GameObject();
	TransformComp* transform = gameObj->AddComponent<TransformComp>();
	transform->x = 100;
	transform->y = 100;
	transform->scaleX = 100.f;
	transform->scaleY = 100.f;
	transform->rotation = 0;
	RendererComp* renderComp = gameObj->AddComponent<RendererComp>(txtManager.get());
	renderComp->setTexture("C:/QuarkEngine/QuarkGame/assets/pngTest.jpg"); 
	gameObjects.push_back(gameObj);
	for (GameObject* object : gameObjects)
	{
		object->Start();
	}

	running = true;
	return true;
	
}

void EngineCore::RendererFrame()
{
	if (!rendererI)
	{
		// Log error or break here
		std::cerr << "Renderer not initialized!" << std::endl;
		return;
	}
	frameNum++;

	rendererI->BeginFrame();
	//bgfx::dbgTextClear();
	//bgfx::dbgTextPrintf(0, 0, 0x0f, "Frame: %llu", frameNum);
	
	/*for (GameObject* object : gameObjects)
	{
		object->Render();
	}*/
	
	gameObj->Render();
	

	rendererI->EndFrame();
}

void EngineCore::RunMainLoop() {
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
			
		}
		SDL_Delay(16);  // ~60fps delay
		timeManager->update();
		RendererFrame();
	}
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
