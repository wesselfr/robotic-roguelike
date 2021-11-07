#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>

struct ShaderData 
{
	unsigned int shaderID = 0;
	GLenum shaderType = 0;
};

enum class ShaderType 
{
	Vertex,
	Fragment
};

class ShaderLoader 
{
private:
	ShaderData _lastShader;
public:
	int LoadDefaultShaders();
	int LoadLineShader();
	int LoadTextShader();
private:
	int LinkShaders(const ShaderData& vertex, const ShaderData& fragment);
	ShaderData LoadShader(const char* file, ShaderType type);
	int LoadFile(const char* file, std::string* out);
};