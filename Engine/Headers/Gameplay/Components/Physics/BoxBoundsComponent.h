#pragma once
#include "..\Component.h"
#include "Physics\AABB.h"

class BoxBoundsComponent 
{
public:
	BoxBoundsComponent() {}
private:
	AABB _aabb;
};