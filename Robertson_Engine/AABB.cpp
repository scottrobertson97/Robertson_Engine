#include "AABB.h"



AABB::AABB(glm::vec3 min, glm::vec3 max)
{
	this->min = min;
	this->max = max;
	type = aabb;
}

AABB::AABB()
{
	min = glm::vec3(-0.5f, -0.5f, -0.5f);
	max = glm::vec3( 0.5f,  0.5f,  0.5f);
	type = aabb;
}


AABB::~AABB()
{
}
