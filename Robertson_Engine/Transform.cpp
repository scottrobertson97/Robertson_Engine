#include "Engine.h"
#include "Transform.h"

Transform::Transform()
{
	position = vec3(0);
	rotation = glm::yawPitchRoll(0, 0, 0);;
	scale = mat4();
	
}

Transform::Transform(float x, float y, float z)
{
	position = vec3(x, y, z);
	rotation = glm::yawPitchRoll(0, 0, 0);;
	scale = mat4();
}

Transform::~Transform()
{
}
