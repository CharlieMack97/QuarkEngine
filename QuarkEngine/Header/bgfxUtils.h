#pragma once

#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <bx/readerwriter.h>
#include <bx/string.h>
bgfx::ProgramHandle loadProg(const char* _vsName, const char* _fsName, const char* shaderFolder);
bgfx::ShaderHandle loadShader(const char* name);
bgfx::ShaderHandle loadEmbeddedShader(const uint8_t* data, size_t size);
bgfx::ShaderHandle loadEmbeddedShaderHandle(const uint8_t* data, size_t size, const char* name);