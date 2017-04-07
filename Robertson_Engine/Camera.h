#pragma once
#include "Transform.h"
#include <glm\gtx\transform.hpp>

using glm::mat4;
using glm::mat3;
using glm::vec3;

class Camera
{
private:
	mat4 worldView;

	Transform transform;

	float sensitivity;
public:
	Camera();
	~Camera();
	void start();
	void upload();
	void update();
	void move();
	void turn();
};

