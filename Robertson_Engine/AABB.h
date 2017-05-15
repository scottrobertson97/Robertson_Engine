#pragma once
#include "CollisionBound.h"
class AABB :
	public CollisionBound
{
public:
	glm::vec3 min;
	glm::vec3 max;
	AABB(glm::vec3 min, glm::vec3 max);
	AABB();
	~AABB();
};

