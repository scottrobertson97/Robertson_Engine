#pragma once
#include <glm\gtx\transform.hpp>

enum BoundType { aabb, sphere };

class CollisionBound
{
public:
	
	glm::vec3 offset;
	BoundType type;
	float radius;
	glm::vec3 min;
	glm::vec3 max;

	CollisionBound();
	virtual ~CollisionBound();
};

