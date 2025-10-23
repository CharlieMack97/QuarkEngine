#include "Renderer.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
bool Renderer::Init(void* nativeWindowHandle, uint32_t width, uint32_t height)
{
	bgfx::Init init;
	init.type = bgfx::RendererType::Count;
	init.resolution.width = width;
	init.resolution.height = height;
	init.resolution.reset;


	if (bgfx::init(init))
	{
		return true;
	}
	else {
		return false;
	}

}

void Renderer::Shutdown()
{
	bgfx::shutdown();
}

void Renderer::BeginFrame()
{
	bgfx::touch(0);
}

void Renderer::EndFrame()
{
	bgfx::frame();
}
