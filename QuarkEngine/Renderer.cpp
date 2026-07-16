#include "Renderer.h"
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <SDL3/SDL.h>
#include <filesystem>
#include <bx/math.h>
#include <iostream>
#include "imgui.h"
#include "backends/imgui_impl_sdl3.h"
#include "imgui_bgfx_impl.h"
bool Renderer::Init()
{
	m_width = 1600;
	m_hieght = 900;
	bgfx::renderFrame();
	SDL_SetError("SDL Init failed logging test");
	if (SDL_Init(SDL_INIT_VIDEO) == false) {
		std::cerr << "SDL_Init failed: " << SDL_GetError() << '\n';
		return false;
	}
	window = SDL_CreateWindow("Hello QuarkEngine!", m_width, m_hieght, SDL_WINDOW_RESIZABLE);
	if (!window) {
		std::cerr << "Window creation failed: " << SDL_GetError() << '\n';
		SDL_Quit();
		return false;
	}
	m_reset = BGFX_RESET_VSYNC;
	bgfx::Init init;
	init.type = bgfx::RendererType::Count;
	init.resolution.width = m_width;
	init.resolution.height = m_hieght;
	init.resolution.reset = 0;
	init.platformData.nwh = SDL_GetPointerProperty(SDL_GetWindowProperties(window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
	init.resolution.reset = m_reset;
	if (bgfx::init(init) == false)
	{
	std:printf("bgfx did not init");
		return false;
	}
	//imgui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2((float)m_width, (float)m_hieght);
	//backends init
	ImGui_ImplSDL3_InitForOther(window);   
	ImGui_Implbgfx_Init(255);             
	return true;
}

void Renderer::Shutdown()
{
	ImGui_Implbgfx_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	bgfx::shutdown();
}

void Renderer::BeginFrame()
{
	 

	//Ortho projection (no perspective, just flat)
	//float view[16], proj[16];

	// Set up an orthographic projection for 2D rendering
	//bx::mtxOrtho(proj, 0.0f, 800.f,0.f,600.f,0.f,1.f,1000.f, bgfx::getCaps()->homogeneousDepth);
	//bx::mtxIdentity(view); //Identity matrix for no camera rotation/translation

	// Apply the view and projection
	//bgfx::setViewTransform(ClearView, view, proj);

	// Set clear color and depth (gray background with depth)
	//bgfx::setViewClear(ClearView, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x808080ff, 1.0f, 0);
	//bgfx::setViewMode(0, bgfx::ViewMode::Default);
	// Set the view rectangle (match the window size)
	//bgfx::reset(m_width, m_hieght, BGFX_RESET_VSYNC);
	{
		float proj[16];
		float view[16];
		bx::mtxIdentity(view);

		bgfx::setViewRect(ClearView, 0, 0, static_cast<uint16_t>(m_width), static_cast<uint16_t>(m_hieght));
		bgfx::setViewClear(ClearView, BGFX_CLEAR_COLOR, 0x00FFFFFF);
		bx::mtxOrtho(proj, 0.0f, (float)m_width, (float)m_hieght, 0.0f, -10.0f, 0.0f, 0.f, bx::Handedness::Left);
		//bgfx::setViewTransform(0, NULL, proj);
		
		bgfx::setViewTransform(ClearView, view, proj);

		
		// Call touch to update view
	}
	//imgui rendering
	ImGui_ImplSDL3_NewFrame();
	ImGui_Implbgfx_NewFrame();
	ImGui::NewFrame();


	bgfx::touch(ClearView);
}

void Renderer::EndFrame()
{
	ImGui::Render();
	ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());
	
	bgfx::frame();
}

void Renderer::clear(float a, float b, float c, float d)
{
	uint32_t color =
		(uint32_t(a * 255) << 24) |
		(uint32_t(b* 255) << 16) |
		(uint32_t(c * 255) << 8) |
		uint32_t(d * 255);

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR, color);
	bgfx::touch(0);
}
//test quad
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
