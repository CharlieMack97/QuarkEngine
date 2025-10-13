#include "EngineCore.h"

//void RunEngine() {
//	SDL_Window* window = SDL_CreateWindow("Hello QuarkEngine!", 800, 600, SDL_WINDOW_RESIZABLE);
//	if (!window) {
//		std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
//		return;
//	}
//
//	bool running = true;
//	SDL_Event event;
//	while (running) {
//		while (SDL_PollEvent(&event)) {
//			if (event.type == SDL_EVENT_QUIT)
//				running = false;
//		}
//		SDL_Delay(16);
//	}
//
//	SDL_DestroyWindow(window);
//}
EngineCore::EngineCore() {
	// Constructor code here
}

EngineCore::~EngineCore() {
	// Destructor code here
}

bool EngineCore::Initialize() 
{

	bgfx::Init init;

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

	running = true;
	return true;
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
	}
}

void EngineCore::Shutdown() {
	if (window) {
		SDL_DestroyWindow(window);
		window = nullptr;
	}
	SDL_Quit();
}