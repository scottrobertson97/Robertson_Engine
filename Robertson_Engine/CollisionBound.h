#pragma once
#include <glm\gtx\transform.hpp>
class CollisionBound
{
public:
	glm::vec3 position;

	CollisionBound();
	virtual ~CollisionBound();
};

