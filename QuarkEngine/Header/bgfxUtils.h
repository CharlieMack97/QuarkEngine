#pragma once

#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <bx/readerwriter.h>
#include <bx/string.h>
bgfx::ProgramHandle loadProg(const bx::StringView& _vsName, const bx::StringView& _fsName, const char* shaderFolder);
bgfx::ShaderHandle loadShader(bx::StringView name, const char* shaderFolder);
const bgfx::Memory* loadEmbeddedShader(const uint8_t* data, size_t size);
bgfx::ShaderHandle loadEmbeddedShaderHandle(const uint8_t* data, size_t size, const char* name);