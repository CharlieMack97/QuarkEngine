#pragma once

#include "InterfaceRenderer.h"

class Renderer : public InterfaceRenderer
{

	bool Init(void* nativeWindowHandle, uint32_t width, uint32_t height) override;
	void Shutdown() override;
	void BeginFrame() override;
	void EndFrame() override;

};

