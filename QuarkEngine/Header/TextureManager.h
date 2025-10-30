#pragma once
#include <unordered_map>
#include <string>
#include <bgfx/bgfx.h>
//neeed a library to load an image in and data to give to bgfx in pixels

class TextureManager {
	struct TextureResource
	{
		bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;
		int width = 0;
		int height = 0;
	};

public:
	static bgfx::TextureHandle loadTexture(std::string& path);
	static void shutdown();

private:
	static std::unordered_map<std::string, TextureResource> textures;
	static bgfx::TextureHandle loadFromFile(std::string& path);
};
