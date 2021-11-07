#pragma once
#include <glm\vec3.hpp>

float Lerp(float a, float b, float t) 
{
	return (1.f - t) * a + t * b;
}

glm::vec3 Lerp(const glm::vec3& a, const glm::vec3& b, float t) 
{
	return (1.f - t) * a + b * t;
}

glm::vec2 Lerp(const glm::vec2& a, const glm::vec2& b, float t) 
{
	return (1.f - t) * a + b * t;
}