#pragma once
#include "API.h"

class Texture
{
public:
	ENGINE_API Texture(const char* fileName);
	ENGINE_API void Free();
	ENGINE_API int GetWidth() const;
	ENGINE_API int GetHeight() const;
	ENGINE_API int GetColourChannels() const;
	ENGINE_API unsigned char* GetData() const;
private:
	int _width = 0;
	int _height = 0;
	int _comp = 0;
	unsigned char* _data = 0;
};
