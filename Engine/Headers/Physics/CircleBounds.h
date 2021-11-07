#pragma once
#include "AbstractBounds.h"
#include "Ray.h"

class CircleBounds : public AbstractBounds
{
public:
	CircleBounds(Transform* transform, float radius);
	bool Intersect(const CircleBounds& other) const;
	bool Intersect(const Ray& ray) const;
	float GetRadius() const;
private:
	float _radius = 0.f;
};