#pragma once
#include "CollisionBound.h"
class Sphere :
	public CollisionBound
{
public:
	float raduis;
	Sphere();
	~Sphere();
};

