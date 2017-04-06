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
	vec3 move;

	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_LEFT) == GLFW_PRESS)
		move += vec3(-1, 0, 0);

	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_RIGHT) == GLFW_PRESS)
		move += vec3(1, 0, 0);

	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_UP) == GLFW_PRESS)
		move += vec3(0, 0, -1);

	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_DOWN) == GLFW_PRESS)
		move += vec3(0, 0, 1);

	if(move != vec3())
		transform.push(transform.rotation * glm::normalize(move) * 5.f);

	else
		transform.drag(50);
}

void Camera::turn()
{
	/*get the cursor position*/
	double x;
	double y;
	glfwGetCursorPos(Engine::window.pointer, &x, &y);

	//turn the camera
	transform.turn
	(
		(float)(sensitivity * (Engine::window.height / 2 - y)),
		(float)(sensitivity * (Engine::window.width / 2 - x)),
		0
	);

	//clamp x-axis rotation
	transform.eulerRoation.x = glm::clamp(transform.eulerRoation.x, -1* glm::half_pi<float>(), glm::half_pi<float>());

	//move cursor to the middle of the screen
	glfwSetCursorPos(Engine::window.pointer, Engine::window.halfWidth, Engine::window.halfHeight);
}
