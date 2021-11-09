#pragma once
#include "QuadVisual.h"
#include "API.h"

class TileVisual : public QuadVisual 
{
public:
	ENGINE_API TileVisual(){}
	ENGINE_API TileVisual(int id, const Texture& texture, int spriteWidth = 32, int spriteHeight = 32);
	ENGINE_API void Init();
	ENGINE_API void SetSprite(int id, const Texture& texture, int spriteWidth = 32, int spriteHeight = 32);
private:

};