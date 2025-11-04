#include "RendererComp.h"
#include "GameObject.h" 
#include "TransformComp.h"
#include "bgfxUtils.h"
#include "TextureManager.h"
#include <filesystem>
#include "../../out/build/x64-Debug/include/generated/shaders/dx11/vs_shader.sc.bin.h"
#include "../../out/build/x64-Debug/include/generated/shaders/dx11/fs_shader.sc.bin.h"
struct PosColorVertex
{

	float x;
	float y;
	float z;

	static void init()
	{
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout layout;
};
bgfx::VertexLayout PosColorVertex::layout;
static PosColorVertex vertices[] =
{
	{ -1.f,  1.f},
	{  1.f,  1.f},
	{ -1.f, -1.f},
	{  1.f, -1.f}
};
const uint16_t indices[] = { 0, 1, 2, 1, 3, 2 };


void RendererComp::Start()
{
	
	TransformComp* transform = gameObj->GetComponent<TransformComp>();
	if (transform == nullptr)
	{
		return;
	}
	//bx::mtxScale(matrixScale, transform->scaleX, transform->scaleY, 1.f);
	//bx::mtxRotateZ(matrixRotate, transform->rotation);
	//bx::mtxTranslate(matrixTranslate, transform->x, transform->y, 0.f);

	
	bx::mtxIdentity(matrixScale);
	bx::mtxIdentity(matrixRotate);
	bx::mtxIdentity(matrixTranslate);
	bx::mtxIdentity(matrix);
	//bx::mtxMul(matrix, matrixScale, matrixRotate);
	//bx::mtxMul(matrix, matrix, matrixTranslate);
	
	vsh = loadEmbeddedShaderHandle(vs_shader_dx11, sizeof(vs_shader_dx11), "vs_shader");
	fsh = loadEmbeddedShaderHandle(fs_shader_dx11, sizeof(fs_shader_dx11), "fs_shader");
	program = bgfx::createProgram(vsh,fsh,true);

	

	
	
	PosColorVertex::init();

	vertex = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), PosColorVertex::layout);
	index = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices)));
	//s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
}
void RendererComp::setTexture(const std::string& path)
{
	texture = textManager->loadTexture(path);
}
void RendererComp::Render(uint32_t screenWidth, uint32_t screenHeight)
{
	//if (!bgfx::isValid(texture) || !bgfx::isValid(vertex) || !bgfx::isValid(index))
	//{
	//	return;
	//}

	bgfx::setState(BGFX_STATE_WRITE_R
		| BGFX_STATE_WRITE_G
		| BGFX_STATE_WRITE_B
		| BGFX_STATE_WRITE_A);
	bgfx::setTransform(matrix);
	bgfx::setVertexBuffer(0, vertex);
	bgfx::setIndexBuffer(index);

	//bgfx::setTexture(0, s_texColor, texture);


	bgfx::submit(0, program);
	
}