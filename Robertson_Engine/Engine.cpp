#include "Engine.h"

//declare static objects
Timer Engine::timer;
Window Engine::window;
Camera Engine::camera;

//model and shader being use for this test of the engine
//Model model;
GameObject ball;
GameObject box;

Shader shader;

Engine::Engine()
{
}

Engine::~Engine()
{
}

bool Engine::start(int width, int height)
{
	//try to create the window, if not return false
	if (!window.start(width, height))
		return false;

	camera.start();

	//change color of the window
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	//load and buffer all the models
	bufferModels();

	//render wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//depthcheck
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	

	//try to load the shader
	if (!shader.load())
	{
		printf("shader did not load");
	}
	
	//use the shader
	shader.use();


	ball.isKinetic = true;
	box.isKinetic = true;
	ball.rigidBody.collisionbound.type = sphere;
	box.rigidBody.collisionbound.type = aabb;

	return true;
}

bool Engine::bufferModels()
{
	//buffer the model
	ball.model.buffer("models/sphere.obj");
	ball.model.texture.load();

	box.model.buffer("models/box.obj");
	box.model.texture.load();
	return false;
}

void Engine::stop()
{
	shader.unload();
	glDeleteTextures(1, &ball.model.texture.texID);
	glDeleteBuffers(1, &ball.model.vertBuf);

	glDeleteTextures(1, &box.model.texture.texID);
	glDeleteBuffers(1, &box.model.vertBuf);
}

void Engine::update()
{
	ball.rigidBody.push(glm::vec3(0.05, 0.05, 0));
	//ball.transform.position = glm::vec3(-1.7, -1.7, 0);

	ball.update();
	box.update();

	ball.isColliding(box);

	timer.update();

	system("cls");

	camera.update();

	//camera loaction
	int cameraLoc = glGetUniformLocation(shader.getProgram(), "cameraLoc");
	glUniform3f(cameraLoc,camera.transform.position.x, camera.transform.position.y, camera.transform.position.z);
}

void Engine::draw()
{
	//clear the canvas
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	//render the model
	ball.render();
	box.render();

	//swap the front and back buffers
	glfwSwapBuffers(window.pointer);
}
