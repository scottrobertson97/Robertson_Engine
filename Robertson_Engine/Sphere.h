#pragma once
#include "CollisionBound.h"
class Sphere :
	public CollisionBound
{
public:
	float raduis;
	glm::vec3 position;
	Sphere();
	~Sphere();
};

