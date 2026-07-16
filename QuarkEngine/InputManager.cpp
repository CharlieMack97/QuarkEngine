#include "InputManager.h"

void InputManager::Update()
{
    previous = current;

    float mx, my;
    Uint32 buttons = SDL_GetMouseState(&mx, &my);

    lastX = mouseX;
    lastY = mouseY;

    mouseX = mx;
    mouseY = my;

    deltaX = mouseX - lastX;
    deltaY = mouseY - lastY;

    current[SDL_BUTTON_LEFT] = (buttons & SDL_BUTTON_LMASK) != 0;
    current[SDL_BUTTON_RIGHT] = (buttons & SDL_BUTTON_RMASK) != 0;
    current[SDL_BUTTON_MIDDLE] = (buttons & SDL_BUTTON_MMASK) != 0;

    keyPrevious = keyCurrent;
    int numKeys = 0;
    const bool* state = SDL_GetKeyboardState(&numKeys);
    for (int i = 0; i < numKeys && i < SDL_SCANCODE_COUNT; ++i)
        keyCurrent[i] = state[i];

}
bool InputManager::IsKeyDown(SDL_Scancode key) const
{
    return keyCurrent[key];
}
bool InputManager::WasKeyPressed(SDL_Scancode key) const
{
    return keyCurrent[key] && !keyPrevious[key];
}
bool InputManager::WasKeyReleased(SDL_Scancode key) const
{
    return !keyCurrent[key] && keyPrevious[key];
}
bool InputManager::IsDown(Uint8 button) const
{
    return current[button];
}

bool InputManager::WasPressed(Uint8 button) const
{
    return current[button] && !previous[button];
}

bool InputManager::WasReleased(Uint8 button) const
{
    return !current[button] && previous[button];
}

