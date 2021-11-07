#pragma once
#include "Gameplay\Transform.h"

// Forward declarations
class CircleBounds;
class AABB;
struct Ray;

class AbstractBounds
{
public:
	AbstractBounds(Transform* transform) : _transform(transform) {}
	virtual bool Intersect(const CircleBounds& other) const = 0;
	virtual bool Intersect(const AABB& other) const = 0;
	virtual bool Intersect(const Ray& ray) const = 0;
	virtual glm::vec3 GetWorldPosition() const { return _transform->GetWorldPosition(); }
private:
	Transform* _transform = nullptr;
};