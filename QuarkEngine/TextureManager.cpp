#include "TextureManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"
#include <iostream>
std::unordered_map<std::string, bgfx::TextureHandle> TextureManager::textures;
bgfx::TextureHandle TextureManager::loadTexture(const std::string& path)
{
	auto it = textures.find(path);
	if (it != textures.end())
	{
		return it->second;
	}
	bgfx::TextureHandle handle = loadFromFile(path);
	if (bgfx::isValid(handle))
	{
		textures[path] = handle;
	}
	return handle;
}

void TextureManager::shutdown()
{
	for (auto& [_, handle] : textures) {
		if (bgfx::isValid(handle)) {
			bgfx::destroy(handle);
		}
	}
	textures.clear();

}

bgfx::TextureHandle TextureManager::loadFromFile(const std::string& path)
{
	int width, hieght, channels;
	auto* data = stbi_load(path.c_str(), &width, &hieght, &channels, 4);
	if (!data)
	{
		std::cerr << "failed" << stbi_failure_reason() << "/n";
		return BGFX_INVALID_HANDLE;
		
	}

	const bgfx::Memory* memPtr = bgfx::copy(data, width * hieght * 4);
	stbi_image_free(data);

	bgfx::TextureHandle handle = bgfx::createTexture2D(uint16_t(width), uint16_t(hieght), false, 1, bgfx::TextureFormat::BGRA8, BGFX_TEXTURE_NONE, memPtr);
	
	if (!bgfx::isValid(handle))
	{
		return BGFX_INVALID_HANDLE;
	}
	return handle;
}
