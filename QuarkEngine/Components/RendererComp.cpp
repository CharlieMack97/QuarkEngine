#include "RendererComp.h"
#include "GameObject.h" 
#include "TransformComp.h"
#include "../lib/bgfx.cmake/bgfx/examples/common/bgfx_utils.h"
#include "TextureManager.h"
#include <bgfx/bgfx.h>
bgfx::VertexLayout RendererComp::vertexLayout::layout;


void RendererComp::init()
{
	
	TransformComp* transform = gameObj->GetComponent<TransformComp>();
	if (transform == nullptr)
	{
		return;
	}
	bx::mtxScale(matrixScale, transform->scaleX, transform->scaleY, 1.f);
	bx::mtxRotateZ(matrixRotate, transform->rotation);
	bx::mtxTranslate(matrixTranslate, transform->x, transform->y, 0.f);


	bx::mtxMul(matrix, matrixScale, matrixRotate);
	bx::mtxMul(matrix, matrix, matrixTranslate);

	program = loadProgram("vs_shader", "fs_shader");

	vertexLayout::init();

	vertexLayout vertices[] =
	{
		{ -0.5f,  0.5f, 0.0f, 0xffffffff, 0.0f, 0.0f },
		{  0.5f,  0.5f, 0.0f, 0xffffffff, 1.0f, 0.0f },
		{ -0.5f, -0.5f, 0.0f, 0xffffffff, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 0xffffffff, 1.0f, 1.0f },
	};
	const uint16_t indices[] = { 0, 1, 2, 1, 3, 2 };


	vertex = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), vertexLayout::layout);
	index = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices)));
	s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
}
void RendererComp::setTexture(const std::string& path)
{
	texture = textManager->loadTexture(path);
}
void RendererComp::Render()
{
	bgfx::setTransform(matrix);
	bgfx::setVertexBuffer(0, vertex);
	bgfx::setIndexBuffer(index);

	bgfx::setTexture(0, s_texColor, texture);
	bgfx::setState(0);
	bgfx::submit(0, program);
}