#include "Renderer.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <SDL3/SDL.h>

bool Renderer::Init(void* nativeWindowHandle, uint32_t width, uint32_t height)
{
	m_hieght = height;
	m_width = width;

	bgfx::Init init;
	init.type = bgfx::RendererType::Count;
	init.resolution.width = width;
	init.resolution.height = height;
	init.resolution.reset = 0;
	init.platformData.nwh = nativeWindowHandle;
	
	bgfx::renderFrame();
	if (!bgfx::init(init))
	{
		return false;
	}
	bgfx::setDebug(BGFX_DEBUG_TEXT );
	


	return true;
}

void Renderer::Shutdown()
{
	bgfx::shutdown();
}

void Renderer::BeginFrame()
{
	bgfx::ViewId ClearView = 0;
	if (m_width > 0 && m_hieght > 0)
	{
		bgfx::setViewClear(ClearView,BGFX_CLEAR_COLOR);
		bgfx::setViewRect(ClearView, 0, 0, static_cast<uint16_t>(m_width), static_cast<uint16_t>(m_hieght));
		bgfx::touch(ClearView);
	}
	
	
}

void Renderer::EndFrame()
{
	bgfx::frame();
}

void Renderer::clear(float a, float b, float c, float d)
{
	uint32_t color =
		(uint32_t(a * 255) << 24) |
		(uint32_t(b* 255) << 16) |
		(uint32_t(c * 255) << 8) |
		uint32_t(d * 255);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, color);
	bgfx::touch(0);
}

void Renderer::DrawTestQuad()
{
	bgfx::dbgTextClear();
	bgfx::dbgTextPrintf(0, 0, 0x0f, "Test draw!");

	bgfx::dbgTextPrintf(10, 5, 0x0f, "DrawTestQuad called");


	bgfx::dbgTextPrintf(0, 10, 0x0f, "Drawing rectangle at 100,100 - 300,250");


	bgfx::dbgTextPrintf(0, 11, 0x0f, "+----------------+");
	bgfx::dbgTextPrintf(0, 12, 0x0f, "|                |");
	bgfx::dbgTextPrintf(0, 13, 0x0f, "|                |");
	bgfx::dbgTextPrintf(0, 14, 0x0f, "+----------------+");

	
	bgfx::dbgTextPrintf(0, 16, 0x0f, "Use bgfx::dbg* APIs for lines/shapes.");
}

void Renderer::Resize(uint32_t width, uint32_t height)
{
}
