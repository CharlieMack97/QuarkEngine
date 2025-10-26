#pragma once
#include "Component.h"
#include "TransformComp.h"
#include "bx/math.h"
#include "bgfx/bgfx.h"
#include "TextureManager.h"

class RendererComp : public Component {

public:
	bgfx::TextureHandle texture = BGFX_INVALID_HANDLE;
	bgfx::ProgramHandle program = BGFX_INVALID_HANDLE;
	RendererComp(TextureManager* textMgr) : textManager(textMgr) {}

	void setTexture(std::string& path)
	{
		texture = textManager->loadTexture(path);
	}
	void Render() override {

		auto* transform = m_GameObj->GetComponent<TransformComp>();
		if (!transform)
		{
			return;
		}
		float matrix[16];
		float matrixScale[16];
		float matrixRotate[16];
		float matrixTranslate[16];

		bx::mtxScale(matrixScale, transform->scaleX, transform->scaleY, 1.f);
		bx::mtxRotateZ(matrixRotate, transform->rotation);
		bx::mtxTranslate(matrixTranslate, transform->x, transform->y, 0.f);


		bx::mtxMul(matrix, matrixScale, matrixRotate);
		bx::mtxMul(matrix, matrix, matrixTranslate);

		bgfx::setTransform(matrix);

		//bgfx::setTexture(0,,)

		bgfx::submit(0, program);

	}
private:
	TextureManager* textManager;

};