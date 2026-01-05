#include "RendererComp.h"
#include "GameObject.h" 
#include "TransformComp.h"
#include "bgfxUtils.h"
#include "TextureManager.h"
#include <filesystem>
//#include "../../out/build/x64-Debug/include/generated/shaders/dx11/vs_shader.sc.bin.h"
//#include "../../out/build/x64-Debug/include/generated/shaders/dx11/fs_shader.sc.bin.h"
//#include "../lib/bgfx.cmake/bgfx/include/bgfx/embedded_shader.h"
//#include <../../out/build/x64-Debug/QuarkEngine/include/generated/shaders/vs_shader.sc.bin.h>

//#include "C:/cmp315/QuarkEngine/out/build/x64-Debug/include/generated/shaders/dx11/fs_shader.sc.bin.h"
//#include "C:/cmp315/QuarkEngine/out/build/x64-Debug/include/generated/shaders/dx11/vs_shader.sc.bin.h"

#include "../shader/fs_shader.sc.bin.h"
#include "../shader/vs_shader.sc.bin.h"


struct PosColorVertex
{

	float m_x;
	float m_y;
	float m_z;
	uint32_t abgr;
	float m_u;
	float m_v;
	static void init()
	{
		m_layout;
		m_layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
	}

	static bgfx::VertexLayout m_layout;
};
bgfx::VertexLayout PosColorVertex::m_layout;
static PosColorVertex vertices[] =
{
	{-0.5f, 0.5f,0.0f,0xffffffff,0.f,1.f},
	{0.5f, 0.5f,0.0f,0xffff00ff,1.f,1.f},
	{0.5f, -0.5f,0.0f,0xffffffff,1.f,0.f},
	{-0.5f, -0.5f,0.0f,0xffff00ff,0.f,0.f},
};
static const uint16_t indices[] = {2,1,0,0,3,2};


void RendererComp::Start()
{
	
	PosColorVertex::init();
	vertex = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), PosColorVertex::m_layout);
	index = bgfx::createIndexBuffer(bgfx::makeRef(indices, sizeof(indices)));


	TransformComp* transform = gameObj->GetComponent<TransformComp>();
	if (transform == nullptr)
	{
		return;
	}
	bx::mtxIdentity(matrixScale);
	bx::mtxIdentity(matrixRotate);
	bx::mtxIdentity(matrixTranslate);
	bx::mtxIdentity(matrix);
	
	
	bx::mtxScale(matrixScale, transform->scaleX, transform->scaleY, 1.f);
	bx::mtxRotateZ(matrixRotate, transform->rotation);
	bx::mtxTranslate(matrixTranslate, transform->x, transform->y, 0.f);

	
	bx::mtxMul(matrix, matrixScale, matrixRotate);
	bx::mtxMul(matrix, matrix, matrixTranslate);

	auto vs = loadEmbeddedShader(vs_shader_dx11, sizeof(vs_shader_dx11));
	auto fs = loadEmbeddedShader(fs_shader_dx11, sizeof(fs_shader_dx11));
	
	program = bgfx::createProgram(vs,fs,true);
	if (!bgfx::isValid(vs))
		printf("Vertex shader failed to load!\n");
	else
		printf("Vertex shader loaded, handle id: %u\n", vs.idx);

	if (!bgfx::isValid(fs))
		printf("Fragment shader failed to load!\n");
	else
		printf("Fragment shader loaded, handle id: %u\n", fs.idx);

	if (!bgfx::isValid(program))
		printf("Program failed to create!\n");
	else
		printf("Program created successfully, handle id: %u\n", program.idx);
	s_texColor = bgfx::createUniform("s_texColor", bgfx::UniformType::Sampler);
	
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

	TransformComp* transform = gameObj->GetComponent<TransformComp>();
	if (!transform) return;

	// Recalculate transform matrix from current position/rotation/scale
	bx::mtxIdentity(matrixScale);
	bx::mtxIdentity(matrixRotate);
	bx::mtxIdentity(matrixTranslate);
	bx::mtxIdentity(matrix);

	bx::mtxScale(matrixScale, transform->scaleX, transform->scaleY, 1.f);
	bx::mtxRotateZ(matrixRotate, transform->rotation);
	bx::mtxTranslate(matrixTranslate, transform->x, transform->y, 0.f);

	bx::mtxMul(matrix, matrixScale, matrixRotate);
	bx::mtxMul(matrix, matrix, matrixTranslate);

	bgfx::setVertexBuffer(0, vertex);
	bgfx::setIndexBuffer(index);

	bgfx::setTransform(matrix);
	/*bgfx::setState(BGFX_STATE_DEFAULT);*/
	bgfx::setState(
		BGFX_STATE_WRITE_RGB
		| BGFX_STATE_WRITE_A
		| BGFX_STATE_BLEND_ALPHA
		/*| BGFX_STATE_PT_TRISTRIP*/
		
	);

	bgfx::setTexture(0, s_texColor, texture);
	bgfx::submit(0, program);
	
}
void RendererComp::Destroy()
{
	bgfx::destroy(vertex);
	bgfx::destroy(index);
}