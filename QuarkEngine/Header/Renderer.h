#pragma once
#include "InterfaceRenderer.h"
#include <bgfx/bgfx.h>
#include <SDL3/SDL.h>
class Renderer : public InterfaceRenderer
{

	bool Init() override;
	void Shutdown() override;
	void BeginFrame() override;
	void EndFrame() override;
	void clear(float a,float b,float c,float d);
	void DrawTestQuad() override;
	void Resize(uint32_t width, uint32_t height) override;
private:
	uint32_t m_width;
	uint32_t m_hieght;
	uint32_t m_reset;
	SDL_Window* window = nullptr;
	bgfx::ViewId ClearView;

};

