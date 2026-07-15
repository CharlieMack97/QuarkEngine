#pragma once
#include <SDL3/SDL.h>
#include <string>

inline std::string AssetPath(const std::string& relativePath)
{
    static std::string base = SDL_GetBasePath(); // cached — base path doesn't change at runtime
    return base + "assets/" + relativePath;
}