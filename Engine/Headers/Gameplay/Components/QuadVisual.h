#pragma once
#include "Resources\ShaderLoader.h"
#include "Primitives\Quad.h"
#include "Gameplay\Transform.h"
#include "VisualComponent.h"
#include "API.h"

class QuadVisual : public VisualComponent
{
public:
	ENGINE_API QuadVisual() {}
	ENGINE_API void Init()
	{
		ShaderLoader shaderLoader;
		_quad.Init(shaderLoader.LoadDefaultShaders(), _transform);
		_quad.SetTexture("Assets/Textures/TestTileset.png");
	}
	ENGINE_API void Draw(glm::mat4 viewProjection)
	{
		_quad.Draw(viewProjection);
	}
	ENGINE_API void Shutdown()
	{
		_quad.Dispose();
	}
protected:
	Quad _quad;
};