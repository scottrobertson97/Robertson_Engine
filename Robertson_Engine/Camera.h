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

	float zoom;
	float fovy;
	float aspect;
	float zNear;
	float zFar;
	mat4 perspective;
public:
	Camera();
	~Camera();
	void start();
	void upload();
	void update();
	void move();
	void turn();
};

