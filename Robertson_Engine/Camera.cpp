/*
		~~Notes~~
move a lot of the updating to the transform class
*/


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

	transform = Transform
	(
		vec3(0, 0, 1),
		vec3(0, 0, 0),
		1,
		1
	);


	/*should be moved to transform class*/
	//eulerRoation = { 0.f,0.f,0.f };
	//position = { 0,0,1 };
	//velocity = { 0,0,0 };
	//rotation = mat3(glm::yawPitchRoll(eulerRoation.y, eulerRoation.x, eulerRoation.z));
	//speed = 0.02f;

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

	transform.drag(5.f);
	transform.update();

	vec3 eye = transform.position;
	vec3 center = eye + transform.rotation * vec3(0, 0, -1);
	vec3 up = transform.rotation * vec3(0, 1, 0);

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
	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_LEFT) == GLFW_PRESS)
		transform.push(transform.rotation * vec3(-1, 0, 0));
	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_RIGHT) == GLFW_PRESS)
		transform.push(transform.rotation * vec3(1, 0, 0));
	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_UP) == GLFW_PRESS)
		transform.push(transform.rotation * vec3(0, 0, -1));
	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_DOWN) == GLFW_PRESS)
		transform.push(transform.rotation * vec3(0, 0, 1));
}

void Camera::turn()
{
	double x;
	double y;
	glfwGetCursorPos(Engine::window.pointer, &x, &y);

	transform.turn
	(
		(float)(sensitivity * (Engine::window.height / 2 - y)),
		(float)(sensitivity * (Engine::window.width / 2 - x)),
		0
	);

	transform.eulerRoation.x = glm::clamp(transform.eulerRoation.x, -1* glm::half_pi<float>(), glm::half_pi<float>());
	glfwSetCursorPos(Engine::window.pointer, Engine::window.halfWidth, Engine::window.halfHeight);
	transform.rotation = mat3(glm::yawPitchRoll(transform.eulerRoation.y, transform.eulerRoation.x, transform.eulerRoation.z));
}
