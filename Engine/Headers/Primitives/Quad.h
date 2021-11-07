#pragma once
#include<glm\glm.hpp>
#include<glm\gtx\transform.hpp>
#include "Gameplay\Transform.h"
#include "Resources\Texture.h"

class Quad 
{
private:
	unsigned int _VBO, _EBO, _VAO;
	unsigned int _shaderProgram;
	unsigned int _textureID;
	float _vertices[20] = 
	{
		// Positions	// UV coordinates
		1,1,0,			0,0,
		1,-1,0,			0,1,
		-1,-1,0,		1,1,
		-1,1,0,			1,0
	};
	int _indices[6] =
	{
		0,1,3,
		1,2,3
	};

	glm::mat4 _mvp;
	Transform* _transform;

public:
	void Init(unsigned int programID, Transform* transform);
	void Dispose();
	void SetTexture(const Texture& texture);
	void SetUV(glm::vec2 min, glm::vec2 max);
	void Draw(glm::mat4 viewProjection);
};