#pragma once
#include "InterfaceRenderer.h"

class Renderer : public InterfaceRenderer
{

	bool Init(void* nativeWindowHandle, uint32_t width, uint32_t height) override;
	void Shutdown() override;
	void BeginFrame() override;
	void EndFrame() override;
	void clear(float a,float b,float c,float d);
	void DrawTestQuad() override;
	void Resize(uint32_t width, uint32_t height) override;
private:
	uint32_t m_width;
	uint32_t m_hieght;
	
};

