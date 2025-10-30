#pragma once
#include "Component.h"
#include "TransformComp.h"
#include "bx/math.h"
#include "bgfx/bgfx.h"
#include "TextureManager.h"
#include "bgfx.cmake/bgfx/examples/common/bgfx_utils.h"
class RendererComp : public Component {

public:
	bgfx::TextureHandle texture = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle program = BGFX_INVALID_HANDLE;
	bgfx::UniformHandle s_texColor = BGFX_INVALID_HANDLE;
	bgfx::VertexBufferHandle vertex = BGFX_INVALID_HANDLE;
	bgfx::IndexBufferHandle index = BGFX_INVALID_HANDLE;
	RendererComp(TextureManager* textMgr) : textManager(textMgr) {}
	void init()
	{
		TransformComp* transform = m_GameObj->GetComponent<TransformComp>();
		if (transform == nullptr)
		{
			return;
		}
		bx::mtxScale(matrixScale, transform->scaleX, transform->scaleY, 1.f);
		bx::mtxRotateZ(matrixRotate, transform->rotation);
		bx::mtxTranslate(matrixTranslate, transform->x, transform->y, 0.f);


		bx::mtxMul(matrix, matrixScale, matrixRotate);
		bx::mtxMul(matrix, matrix, matrixTranslate);
		s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
		program = loadProgram("vs_shader", "fs_shader");
	}

	void setTexture(std::string& path)
	{
		texture = textManager->loadTexture(path);
	}
	void Render() override {

		bgfx::setTransform(matrix);

		bgfx::setTexture(0, s_texColor, texture);

		bgfx::submit(0, program);

	}
private:
	TextureManager* textManager;
	float matrix[16];
	float matrixScale[16];
	float matrixRotate[16];
	float matrixTranslate[16];
};