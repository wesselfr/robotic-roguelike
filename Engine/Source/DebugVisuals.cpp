#include "DebugVisuals.h"
#include "Resources\ShaderLoader.h"
#include <stdarg.h>

DebugVisuals* DebugVisuals::_instance = nullptr;

void DebugVisuals::Init(float width, float height) 
{
	_instance = this;

	ShaderLoader shaderLoader;

	_lineVisual.Init(shaderLoader.LoadTextShader());
	_textVisual.Init("Assets/Fonts/FallingSkyBlack.otf", 10);
	_textVisual.SetProjection(glm::ortho(0.0f,width, 0.0f,height));
}

void DebugVisuals::DrawLine(glm::vec3 a, glm::vec3 b, glm::vec3 color) 
{
	//Todo: Add colored line support.
	_lineVisual.AddLine(a, b);
}

void DebugVisuals::DrawText(glm::vec3 pos, glm::vec3 color, const char* message, ...) 
{
	va_list args;
	va_start(args, message);

	static char buffer[1024];
	vsnprintf(buffer, 1024, message, args);
	_textVisual.Draw(buffer, glm::vec2(pos.x, pos.y), 1.f, color);

	va_end(args);
}

void DebugVisuals::Draw(glm::mat4 viewProjection) 
{
	_lineVisual.UpdateBuffers();
	_lineVisual.Draw(viewProjection);
	_lineVisual.Clear();
}