#pragma once
#include <SDL3/SDL.h>
#include <array>

class InputManager
{
public:
    void Update();

    bool IsDown(Uint8 button) const;
    bool WasPressed(Uint8 button) const;
    bool WasReleased(Uint8 button) const;

    int X() const { return mouseX; }
    int Y() const { return mouseY; }
    int DeltaX() const { return deltaX; }
    int DeltaY() const { return deltaY; }

private:
    std::array<bool, 8> current{};
    std::array<bool, 8> previous{};

    int mouseX = 0, mouseY = 0;
    int lastX = 0, lastY = 0;
    int deltaX = 0, deltaY = 0;
};
