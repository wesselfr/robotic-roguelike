#include "Gameplay\Components\TileVisual.h"

ENGINE_API TileVisual::TileVisual(int id, const Texture& texture, int spriteWidth, int spriteHeight)
{
	Init();
	SetSprite(id, texture, spriteWidth, spriteHeight);
}

void TileVisual::Init()
{
	ShaderLoader shaderLoader;
	_quad.Init(shaderLoader.LoadDefaultShaders(), _transform);
	//Todo: include some kind of fallback graphics.
}

ENGINE_API void TileVisual::SetSprite(int id, const Texture& texture, int spriteWidth, int spriteHeight)
{
	assert(id > -1 && "ID should not be negative");
	_quad.SetTexture(texture);

	float xCorrection = 0.25f / static_cast<float>(spriteWidth);
	float yCorrection = 0.25f / static_cast<float>(spriteHeight);

	int x = id % (texture.GetWidth()/spriteWidth);
	int y = id / (texture.GetWidth()/spriteWidth);

	float xPosMin = (spriteWidth * x) / static_cast<float>(texture.GetWidth());
	float yPosMin = (spriteHeight * y) / static_cast<float>(texture.GetHeight());

	float xPosMax = (spriteWidth * (x + 1)) / static_cast<float>(texture.GetWidth());
	float yPosMax = (spriteHeight * (y + 1)) / static_cast<float>(texture.GetHeight());

	_quad.SetUV(glm::vec2(xPosMin + xCorrection, yPosMin + yCorrection), glm::vec2(xPosMax - xCorrection, yPosMax - yCorrection));
}
