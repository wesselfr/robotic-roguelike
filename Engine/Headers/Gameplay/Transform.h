#pragma once
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

class Transform
{
protected:
	glm::vec3 _worldPosition = glm::vec3(0, 0, 0);
	glm::vec3 _scale = glm::vec3(1, 1, 1);
	glm::mat4 _rotation = glm::mat4(1);
public:
	ENGINE_API void Translate(glm::vec3 translation);
	ENGINE_API void Scale(glm::vec3 scale);
	ENGINE_API void LookAt(glm::vec3 pos);
	ENGINE_API const glm::vec3& GetWorldPosition();
	ENGINE_API void SetWorldPosition(glm::vec3 worldPos);
	ENGINE_API glm::mat4 GetModelMatrix();
};