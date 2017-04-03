#include "Engine.h"
#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::start()
{
	worldView = mat4();
	camRot = { 0.f,0.f,0.f };
	/*should be moved to transform class*/
	position = { 0,0,1 };
	velocity = { 0,0,0 };
	rotation = mat3(glm::yawPitchRoll(camRot.y, camRot.x, camRot.z));
	speed = 0.02f;
	sensitivity = .005f;
	glfwSetCursorPos(Engine::window.pointer, Engine::window.halfWidth, Engine::window.halfHeight);
	glfwSetInputMode(Engine::window.pointer, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Camera::upload()
{
	glUniformMatrix4fv(4, 1 , GL_FALSE, &worldView[0][0]);
}

void Camera::update()
{
	turn();
	move();

	position += velocity;

	vec3 eye = position;
	vec3 center = eye + rotation * vec3(0, 0, -1);
	vec3 up = rotation * vec3(0, 1, 0);

	mat4 lookatMat = glm::lookAt(eye, center, up);

	/*perspective*/
	float zoom = 1.f;

	float fovy = glm::pi<float>() * 0.4f / zoom;
	float aspect = (float)Engine::window.width / (float)Engine::window.height;
	float zNear = 0.1f;
	float zFar = 1000.f;

	mat4 perspective = glm::perspective(fovy, aspect, zNear, zFar);

	worldView = perspective * lookatMat;

	upload();
}

void Camera::move()
{
	mat3 R = (mat3)glm::yawPitchRoll(camRot.y, camRot.x, camRot.z);

	velocity = { 0,0,0 };
	
	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_LEFT) == GLFW_PRESS)
		velocity += R * vec3(-1, 0, 0);
	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_RIGHT) == GLFW_PRESS)
		velocity += R * vec3(1, 0, 0);
	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_UP) == GLFW_PRESS)
		velocity += R * vec3(0, 0, -1);
	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_DOWN) == GLFW_PRESS)
		velocity += R * vec3(0, 0, 1);
	if (velocity != vec3())
		velocity = glm::normalize(velocity) * speed;
}

void Camera::turn()
{
	double x;
	double y;
	glfwGetCursorPos(Engine::window.pointer, &x, &y);
	camRot.y += (float)(sensitivity * (Engine::window.width / 2 - x));
	camRot.x += (float)(sensitivity * (Engine::window.height / 2 - y));
	camRot.x = glm::clamp(camRot.x, -1* glm::half_pi<float>(), glm::half_pi<float>());
	glfwSetCursorPos(Engine::window.pointer, Engine::window.halfWidth, Engine::window.halfHeight);
	rotation = mat3(glm::yawPitchRoll(camRot.y, camRot.x, camRot.z));
}
