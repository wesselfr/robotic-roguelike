#pragma once
#include "..\Component.h"
#include "Physics\CircleBounds.h"

class CircleBoundsComponent : public Component 
{
public:
	CircleBoundsComponent(Transform* transform, float radius) : _bounds(transform, radius) {}
private:
	CircleBounds _bounds;
};