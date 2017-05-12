#include "Engine.h"
#include "Camera.h"
#include <iostream>
using std::cout;
Camera::Camera() : GameObject()
{
}


Camera::~Camera()
{
}

void Camera::start()
{
	isKinetic = true;

	worldView = mat4();
	transform.position = vec3(0, 0, 5);
	sensitivity = .005f;

	//set cursor to the middle of the screen
	glfwSetCursorPos(Engine::window.pointer, Engine::window.halfWidth, Engine::window.halfHeight);
	//hide the cursor
	glfwSetInputMode(Engine::window.pointer, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	/*perspective*/
	zoom = 1.f;
	fovy = glm::pi<float>() * 0.4f / zoom;
	aspect = (float)Engine::window.width / (float)Engine::window.height;
	zNear = 0.1f;
	zFar = 1000.f;

	perspective = glm::perspective(fovy, aspect, zNear, zFar);
}

void Camera::upload()
{
	glUniformMatrix4fv(4, 1 , GL_FALSE, &worldView[0][0]);
}

void Camera::update()
{
	cout << transform.position.x << " | " << transform.position.y << " | " << transform.position.z << std::endl;
	cout << transform.rotation[0][0] << " | " << transform.rotation[0][1] << " | " << transform.rotation[0][2] << " | " << transform.rotation[0][3] << std::endl;
	cout << transform.rotation[1][0] << " | " << transform.rotation[1][1] << " | " << transform.rotation[1][2] << " | " << transform.rotation[1][3] << std::endl;
	cout << transform.rotation[2][0] << " | " << transform.rotation[2][1] << " | " << transform.rotation[2][2] << " | " << transform.rotation[2][3] << std::endl;
	cout << transform.rotation[3][0] << " | " << transform.rotation[3][1] << " | " << transform.rotation[3][2] << " | " << transform.rotation[3][3] << std::endl;
	turn();
	move();
	
	rigidBody.update();
	//transform = rigidBody.transform;
	
	/*calculating the lookat matrix*/
	vec3 eye = transform.position;
	vec3 center = eye + vec3(transform.rotation * glm::vec4(0, 0, -1, 0));
	vec3 up = vec3(transform.rotation * glm::vec4(0, 1, 0, 0));

	mat4 lookatMat = glm::lookAt(eye, center, up);

	worldView = perspective * lookatMat;

	upload();
}

void Camera::move()
{	
	vec3 move;

	/*based on arrow key pressed add a vector in the direction of key press*/
	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_LEFT) == GLFW_PRESS)
		move += vec3(-1, 0, 0);

	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_RIGHT) == GLFW_PRESS)
		move += vec3(1, 0, 0);

	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_UP) == GLFW_PRESS)
		move += vec3(0, 0, -1);

	if (glfwGetKey(Engine::window.pointer, GLFW_KEY_DOWN) == GLFW_PRESS)
		move += vec3(0, 0, 1);

	//if move is not 0, the move the camera
	if (move != vec3())
	{
		glm::vec4 direction = glm::normalize(glm::vec4(move, 0));
		float power = 5.0f;
		rigidBody.push(vec3(transform.rotation * direction * power));
	}
	//else no key was pressed, so apply friction
	else
		rigidBody.drag(50);
}

void Camera::turn()
{
	/*get the cursor position*/
	double x;
	double y;
	glfwGetCursorPos(Engine::window.pointer, &x, &y);

	//turn the camera
	rigidBody.turn
	(
		(float)(sensitivity * (Engine::window.width / 2 - x)),	//yaw
		(float)(sensitivity * (Engine::window.height / 2 - y)),	//pitch
		0														//roll
	);

	//clamp x-axis rotation
	//transform.eulerRoation.x = glm::clamp(transform.eulerRoation.x, -1* glm::half_pi<float>(), glm::half_pi<float>());

	//move cursor to the middle of the screen
	glfwSetCursorPos(Engine::window.pointer, Engine::window.halfWidth, Engine::window.halfHeight);
}
