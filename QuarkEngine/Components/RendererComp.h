#pragma once
#include "Component.h"
#include "bx/math.h"
#include <bgfx/bgfx.h>
#include <string>


class TextureManager;
class RendererComp : public Component {
	struct vertexLayout
	{
		
		float x, y, z;
		uint32_t rgba;
		float u, v;

		static void init()
		{
			layout.begin()
				.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
				.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true, true)
				.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
				.end();
		}
		static bgfx::VertexLayout layout;
	};
public:
	bgfx::TextureHandle texture = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle program = BGFX_INVALID_HANDLE;
	bgfx::UniformHandle s_texColor = BGFX_INVALID_HANDLE;
	bgfx::VertexBufferHandle vertex = BGFX_INVALID_HANDLE;
	bgfx::IndexBufferHandle index = BGFX_INVALID_HANDLE;
	RendererComp() : textManager(nullptr) {}
	RendererComp(TextureManager* textMgr) : textManager(textMgr) {}
	void init();

	void setTexture(const std::string& path);
	void Render() override;
private:
	TextureManager* textManager;
	float matrix[16];
	float matrixScale[16];
	float matrixRotate[16];
	float matrixTranslate[16];
};