#pragma once
#include "CollisionBound.h"
class Sphere :
	public CollisionBound
{
public:
	float radius;
	Sphere(float radius);
	Sphere();
	~Sphere();
};

