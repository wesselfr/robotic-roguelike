#include "Resources\Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* fileName) 
{
	stbi_set_flip_vertically_on_load(false);
	_data = stbi_load(fileName, &_width, &_height, &_comp, 4);
}

void Texture::Free() 
{
	stbi_image_free(_data);
}

int Texture::GetWidth() const
{
	return _width;
}

int Texture::GetHeight() const
{
	return _height;
}

int Texture::GetColourChannels() const 
{
	return _comp;
}

unsigned char* Texture::GetData() const
{
	return _data;
}