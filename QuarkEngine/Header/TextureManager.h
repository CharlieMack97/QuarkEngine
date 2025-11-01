#pragma once
#include <unordered_map>
#include <string>
#include <bgfx/bgfx.h>


class TextureManager {
	
	struct TextureResource
	{
		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
		int width = 0;
		int height = 0;
	};

public:
	static bgfx::TextureHandle loadTexture(const std::string& path);
	static void shutdown();

private:
	static std::unordered_map<std::string, bgfx::TextureHandle> textures;
	static bgfx::TextureHandle loadFromFile(const std::string& path);
};
