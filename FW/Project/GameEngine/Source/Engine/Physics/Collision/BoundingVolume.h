#ifndef BoundingVolume_h__
#define BoundingVolume_h__

#include "Core/Core.h"

struct AABB2
{
	glm::f32vec2 Min;
	glm::f32vec2 Max;
};

struct Circle
{
	glm::f32vec2	Center;
	float			Radius;
};

#endif // BoundingVolume_h__
