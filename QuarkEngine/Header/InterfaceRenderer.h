#pragma once
#include <cstdint>
class InterfaceRenderer
{
public:
    virtual ~InterfaceRenderer() = default;

    virtual bool Init(void* nativeWindowHandle, uint32_t width, uint32_t height) = 0;
    virtual void Shutdown() = 0;
    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual void DrawTestQuad() = 0;
    virtual void Resize(uint32_t width, uint32_t height) = 0;
};