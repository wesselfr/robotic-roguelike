#include "Physics\AABB.h"
#include "Physics\CircleBounds.h"

AABB::AABB(Transform* transform, glm::vec2 size) : AbstractBounds(transform)
{
	_size = size;
}

bool AABB::Intersect(const AABB& other) const 
{
	const glm::vec3& pos = GetWorldPosition();
	const glm::vec3& otherPos = other.GetWorldPosition();
	
	return (pos.x - _size.x < otherPos.x + other._size.x &&
			pos.x + _size.x > otherPos.x - other._size.x &&
			pos.y - _size.y < otherPos.y + other._size.y &&
			pos.y + _size.y > otherPos.y - other._size.y);
}

bool AABB::Intersect(const CircleBounds& other) const
{
	glm::vec3 closestPoint = ClosestPointOnAABB(other.GetWorldPosition());
	glm::vec3 difference = other.GetWorldPosition() - closestPoint;

	float distanceSquared = (difference.x * difference.x) + (difference.y * difference.y) + (difference.z + difference.z);
	float radiusSquared = other.GetRadius() * other.GetRadius();

	return distanceSquared < radiusSquared;
}

bool AABB::Intersect(const Ray& ray) const 
{
	float maxS = 0.0f;
	float minT = INFINITY;
	float s, t, recip;
	glm::vec3 pos = GetWorldPosition();
	glm::vec2 min = glm::vec2(pos.x, pos.y) - _size;
	glm::vec2 max = glm::vec2(pos.x, pos.y) + _size;

	// X coordinate test (ZY planes)
	recip = 1.f / ray.dir.x;
	if (recip > 0.0f) 
	{
		s = (min.x - ray.origin.x) * recip;
		t = (max.x - ray.origin.x) * recip;
	}
	else 
	{
		s = (max.x - ray.origin.x) * recip;
		t = (min.x - ray.origin.x) * recip;
	}

	// Update min/max
	maxS = s;
	minT = t;
	if (maxS > minT) { return false; }

	// Y coordinate test (XZ planes)
	recip = 1.f / ray.dir.y;
	if (recip > 0.0) 
	{
		s = (min.y - ray.origin.y) * recip;
		t = (max.y - ray.origin.y) * recip;
	}
	else 
	{
		s = (max.y - ray.origin.y) * recip;
		t = (min.y - ray.origin.y) * recip;
	}

	// Update min/max
	if (s > maxS) 
	{
		maxS = s;
	}
	if (t < minT) 
	{
		minT = t;
	}
	if (maxS > minT) { return false; }

	return true;
}

glm::vec3 AABB::ClosestPointOnAABB(glm::vec3 point) const
{
	glm::vec3 closestPoint = point;
	const glm::vec3& pos = GetWorldPosition();

	if (point.x > pos.x + _size.x) 
	{
		closestPoint.x = pos.x + _size.x;
	}
	if (point.x < pos.x - _size.x) 
	{
		closestPoint.x = pos.x - _size.x;
	}

	if (point.y > pos.y + _size.y) 
	{
		closestPoint.y = pos.y + _size.y;
	}
	if (point.y < pos.y - _size.y) 
	{
		closestPoint.y = pos.y - _size.y;
	}

	return closestPoint;
}