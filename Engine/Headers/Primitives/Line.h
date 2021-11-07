#pragma once
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include "Gameplay\Transform.h"

class Line
{
private:
	unsigned int _VBO, _VAO;
	unsigned int _shaderProgram;
	std::vector<glm::vec3> _vertices;
	glm::vec4 _color = glm::vec4(0,1,0,1);
	glm::mat4 _mvp = glm::mat4(1.f);
public:
	void Init(unsigned int programID);
	void Dispose();
	void Clear();
	void AddLine(glm::vec3 min, glm::vec3 max);
	void UpdateBuffers();
	void Draw(glm::mat4 viewProjection);
};