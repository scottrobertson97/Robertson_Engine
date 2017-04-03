#pragma once
#include <glm\gtx\transform.hpp>

using glm::mat4;
using glm::mat3;
using glm::vec3;

class Camera
{
private:
	mat4 worldView;
	vec3 camRot;
	/*should be movied into a transform class*/
	vec3 position;
	vec3 velocity;
	mat3 rotation;
	float speed;
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

