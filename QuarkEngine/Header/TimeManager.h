#pragma once
#include <SDL3/SDL.h>

class TimeManager
{
public:
	void init() {
		lastTick = SDL_GetTicks();
	}
	void update() {
		Uint64 currTick = SDL_GetTicks();
		Uint64 elapsTick = currTick - lastTick;
		lastTick = currTick;

		deltaTime = elapsTick / 1000.f;
		totalTime += deltaTime;		
	}

	float getDeltaTime() { return deltaTime; }
	float getTotalTime() { return totalTime; }
private:
	Uint64 lastTick = 0;
	float deltaTime = 0.f;
	float totalTime = 0.f;

};

