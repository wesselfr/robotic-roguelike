#pragma once
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtx\transform.hpp>
#include "API.h"

class Camera 
{
protected:
	glm::vec3 _worldPosition = glm::vec3(0, 0, 20);
public:
	Camera(glm::vec3 pos, int width, int height, bool useOrthographic = true) : _worldPosition(pos), _aspectRatio((float)width / (float)height) 
	{
		if (useOrthographic) {
			_projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
			_view = glm::lookAt(pos - glm::vec3(0, 0, 20), pos, glm::vec3(0, 1, 0));
		}
		else {
			_projection = glm::perspective(glm::radians(45.f), _aspectRatio, 0.1f, 100.f);
			_view = glm::lookAt(pos - glm::vec3(0,0,20), pos, glm::vec3(0, 1, 0));
		}
	}
	~Camera() {}

	ENGINE_API virtual void Update(float deltaTime) {}
	ENGINE_API void SetPosition(glm::vec3 pos);
	ENGINE_API glm::mat4 GetViewProjection() const;
private:
	glm::mat4 _view = glm::mat4(0);
	glm::mat4 _projection = glm::mat4(0);
	float _aspectRatio = 0.0f;
};