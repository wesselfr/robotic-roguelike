#pragma once
#include "AbstractBounds.h"
#include "Ray.h"
#include "API.h"

class AABB : public AbstractBounds
{
public:
	ENGINE_API AABB(Transform* transform, glm::vec2 size);
	ENGINE_API bool Intersect(const AABB& other) const;
	ENGINE_API bool Intersect(const CircleBounds& other) const;
	ENGINE_API bool Intersect(const Ray& ray) const;
	ENGINE_API glm::vec3 ClosestPointOnAABB(glm::vec3 position) const;
private:
	glm::vec2 _size;
};