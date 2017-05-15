#include "Sphere.h"



Sphere::Sphere(float radius)
{
	this->radius = radius;
	type = sphere;
}

Sphere::Sphere()
{
	radius = 0.5f;
	type = sphere;
}


Sphere::~Sphere()
{
}
