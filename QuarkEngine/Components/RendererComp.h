#pragma once
#include "Component.h"
#include "bx/math.h"
#include <bgfx/bgfx.h>
#include <string>


class TextureManager;
class RendererComp : public Component {

public:
	bgfx::TextureHandle texture = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle program = BGFX_INVALID_HANDLE;
	bgfx::UniformHandle s_texColor = BGFX_INVALID_HANDLE;
	bgfx::VertexBufferHandle vertex = BGFX_INVALID_HANDLE;
	bgfx::IndexBufferHandle index = BGFX_INVALID_HANDLE;
	bgfx::ShaderHandle vsh = BGFX_INVALID_HANDLE;
	bgfx::ShaderHandle fsh = BGFX_INVALID_HANDLE;
	RendererComp() : textManager(nullptr) {}
	RendererComp(TextureManager* textMgr) : textManager(textMgr) {}
	void Start();
	void Destroy();
	void setTexture(const std::string& path);
	void Render(uint32_t screenWidth, uint32_t screenHeight) override;
private:
	TextureManager* textManager;
	float matrix[16];
	float matrixScale[16];
	float matrixRotate[16];
	float matrixTranslate[16];
};