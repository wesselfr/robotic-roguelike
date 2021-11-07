#include "Physics\CircleBounds.h"

CircleBounds::CircleBounds(Transform* transform, float radius) : AbstractBounds(transform)
{
	_radius = radius;
}

bool CircleBounds::Intersect(const CircleBounds& other) const
{
	glm::vec3 centerDiff = GetWorldPosition() - other.GetWorldPosition();
	float radiusSum = _radius + other._radius;
	return glm::dot(centerDiff,centerDiff) <= radiusSum*radiusSum;
}

// Based on essential mathmathics for interactive applications and games.
bool CircleBounds::Intersect(const Ray& ray) const 
{
	glm::vec3 w = GetWorldPosition() - ray.origin;
	float wsq = glm::dot(w, w);
	float proj = glm::dot(w, ray.dir);
	float rsq = _radius * _radius;

	// Sphere behind ray, no intersection.
	if (proj < 0.0f && wsq > rsq) 
	{
		return false;
	}

	float vsq = glm::dot(ray.dir, ray.dir);
	return (vsq * wsq - proj * proj <= vsq * _radius * _radius);
}

float CircleBounds::GetRadius() const
{
	return _radius;
}