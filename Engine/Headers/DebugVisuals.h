#pragma once
#include "Primitives\Text.h"
#include "Primitives\Line.h"
#include "API.h"

class DebugVisuals 
{
public:
	void Init(float width, float height);
	ENGINE_API void DrawText(glm::vec3 pos, glm::vec3 color, const char* message, ...);
	ENGINE_API void DrawLine(glm::vec3 a, glm::vec3 b, glm::vec3 color);
	void Draw(glm::mat4 viewProjection);

	ENGINE_API static DebugVisuals* GetInstance() { return _instance; }

private:
	static DebugVisuals* _instance;

	Text _textVisual;
	Line _lineVisual;
};
