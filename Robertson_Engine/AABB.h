#pragma once
#include "CollisionBound.h"
class AABB :
	public CollisionBound
{
public:
	glm::vec2 size;
	AABB();
	~AABB();
};

