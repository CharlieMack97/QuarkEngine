#include "bgfxUtils.h"
#include <bx/file.h> 
#include <cstdio>
#include <cstring>
#include <filesystem>

const bgfx::Memory* loadEmbeddedShader(const uint8_t* data, size_t size)
{
    const bgfx::Memory* mem = bgfx::alloc(uint32_t(size));
    bx::memCopy(mem->data, data, size);
    return mem;
}


bgfx::ShaderHandle loadEmbeddedShaderHandle(const uint8_t* data, size_t size, const char* name)
{
    const bgfx::Memory* mem = loadEmbeddedShader(data, size);
    bgfx::ShaderHandle handle = bgfx::createShader(mem);
    bgfx::setName(handle, name);
    return handle;
}



const char* getShaderRoot() { return "C:/QuarkEngine/out/build/x64-Debug/QuarkEngine/shaders/"; }
static const bgfx::Memory* loadMemory(const bx::StringView& filePath)
{
    // Copy StringView into a null-terminated string for fopen
    char path[512];
    bx::memCopy(path, filePath.getPtr(), filePath.getLength());
    path[filePath.getLength()] = '\0';

    FILE* file = fopen(path, "rb");
    if (!file)
    {
        fprintf(stderr, "Failed to open shader file: %s\n", path);
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    const bgfx::Memory* mem = bgfx::alloc(uint32_t(size + 1));
    fread(mem->data, 1, size, file);
    fclose(file);

    mem->data[mem->size - 1] = '\0'; // Null-terminate just in case
    return mem;
}
bgfx::ShaderHandle loadShader(bx::StringView name, const char* shaderFolder)
{
    char filePath[512];
    bx::snprintf(filePath, BX_COUNTOF(filePath),
        "%s%.*s.sc.bin",
        shaderFolder,
        (int)name.getLength(),
        name.getPtr());

    bx::StringView filePathView(filePath, strlen(filePath));
    const bgfx::Memory* mem = loadMemory(filePathView);
    if (!mem)
        return BGFX_INVALID_HANDLE;

    bgfx::ShaderHandle handle = bgfx::createShader(mem);
    bgfx::setName(handle, name.getPtr());
    return handle;
}
bgfx::ProgramHandle loadProg(const bx::StringView& _vsName, const bx::StringView& _fsName, const char* shaderFolder)
{
    bgfx::ShaderHandle vsh = loadShader(_vsName, shaderFolder);
    bgfx::ShaderHandle fsh = loadShader(_fsName, shaderFolder);
    return bgfx::createProgram(vsh, fsh, true);
}