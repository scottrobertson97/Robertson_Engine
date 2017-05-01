#pragma once
#include <glm\gtx\transform.hpp>

using glm::mat4;
using glm::mat3;
using glm::vec3;

class Transform
{
private:
public:
	vec3 position;
	mat4 rotation;
	mat4 scale;

	Transform();
	Transform(float x, float y, float z);
	~Transform();
};

