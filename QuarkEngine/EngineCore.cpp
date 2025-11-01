#include "EngineCore.h"
#include "Renderer.h"
#include "TimeManager.h"
#include "EngineApp.h"
#include <SDL3/SDL.h>
#include "Components/TransformComp.h"
#include "Components/RendererComp.h"
EngineCore::EngineCore() {
	
}

EngineCore::~EngineCore() {
	
}

bool EngineCore::Initialize() 
{

	
	//initilising systems
	timeManager = std::make_unique<TimeManager>();
	timeManager->init();


	SDL_SetError("SDL Init failed logging test");
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
		return false;
	}

	window = SDL_CreateWindow("Hello QuarkEngine!", 800, 600, SDL_WINDOW_RESIZABLE);
	if (!window) {
		std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
		SDL_Quit();
		return false;
	}
	SDL_PropertiesID props = SDL_GetWindowProperties(window);
	void* nativeWindowHandle = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, &nativeWindowHandle);
	rendererI= std::make_unique<Renderer>();
	txtManager = std::make_unique<TextureManager>();
	if (!rendererI->Init(nativeWindowHandle, 800, 600))
	{
		return false;
	}



	//testing obj
	gameObj = new GameObject();
	TransformComp* transform = gameObj->AddComponent<TransformComp>();
	transform->x = 0;
	transform->y = 0;
	transform->scaleX = 100.f;
	transform->scaleY = 100.f;

	RendererComp* renderComp = gameObj->AddComponent<RendererComp>(txtManager.get());
	renderComp->setTexture("QuarkGame/assets/pngTest.jpg");
	gameObjects.emplace_back(gameObj);


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
	rendererI->BeginFrame();
	for (GameObject* object : gameObjects)
	{
		object->Render();
	}
	//rendererI->DrawTestQuad();
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
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	SDL_Quit();
}

TextureManager* EngineCore::getTextureManager()
{
	return txtManager.get();
}
