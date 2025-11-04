#include "Renderer.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <SDL3/SDL.h>
#include <filesystem>
#include <bx/math.h>
bool Renderer::Init(void* nativeWindowHandle, uint32_t width, uint32_t height)
{
	m_hieght = height;
	m_width = width;

	bgfx::Init init;
	init.type = bgfx::RendererType::Count;
	init.resolution.width = width;
	init.resolution.height = height;
	init.resolution.reset = 0;
	init.platformData.ndt = NULL;
	init.platformData.nwh = nativeWindowHandle;
	
	if (!bgfx::init(init))
	{
		return false;
	}
	//bgfx::setDebug(BGFX_DEBUG_TEXT);
	
	bgfx::RendererType::Enum type = bgfx::getRendererType();
	printf("Renderer: %s\n", bgfx::getRendererName(type));

	
	return true;
}

void Renderer::Shutdown()
{
	bgfx::shutdown();
}

//void Renderer::BeginFrame()
//{
//	bgfx::ViewId ClearView = 0;
//	if (m_width > 0 && m_hieght > 0)
//	{
//		bgfx::setViewClear(ClearView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff,1.0f,0);
//		const bx::Vec3 at = { 0.0f, 0.0f,  -1.0f };
//		const bx::Vec3 eye = { 0.0f, 0.0f, 5.0f };
//		float view[16];
//		bx::mtxLookAt(view, eye, at);
//		float proj[16];
//		bx::mtxProj(proj, 60.0f, m_width / m_hieght, 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
//		bgfx::setViewTransform(0, view, proj);
//		bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_hieght));
//		
//		//bgfx::setViewRect(ClearView, 0, 0, static_cast<uint16_t>(m_width), static_cast<uint16_t>(m_hieght));
//		bgfx::touch(ClearView);
//	}
//	
//	
//}
void Renderer::BeginFrame()
{
	bgfx::ViewId ClearView = 0;

	// Ortho projection (no perspective, just flat)
	float view[16], proj[16];

	// Set up an orthographic projection for 2D rendering
	bx::mtxOrtho(proj, 0.0f, 800.f,0.f,600.f,0.f,1.f,1000.f, bgfx::getCaps()->homogeneousDepth);
	bx::mtxIdentity(view); // Identity matrix for no camera rotation/translation

	// Apply the view and projection
	bgfx::setViewTransform(ClearView, view, proj);

	// Set clear color and depth (gray background with depth)
	bgfx::setViewClear(ClearView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x808080ff, 1.0f, 0);
	bgfx::setViewMode(0, bgfx::ViewMode::Default);
	// Set the view rectangle (match the window size)
	bgfx::setViewRect(ClearView, 0, 0, uint16_t(m_width), uint16_t(m_hieght));

	// Call touch to update view
	bgfx::touch(ClearView);
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
