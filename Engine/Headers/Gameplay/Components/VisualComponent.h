#pragma once
#include "Component.h"
#include <glm\vec3.hpp>

class VisualComponent : public Component
{
public:
	virtual void Draw(glm::mat4 viewProjection) {}
	virtual void SetTransform(Transform* transform) { _transform = transform; }
protected:
	Transform* _transform = nullptr;
};