#include "Engine.h"

//declare static objects
Timer Engine::timer;
Window Engine::window;
Camera Engine::camera;

//model and shader being use for this test of the engine
Model model;
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

	//try to load the shader
	if (!shader.load())
	{
		printf("shader did not load");
	}
	
	//use the shader
	shader.use();

	return true;
}

bool Engine::bufferModels()
{
	//buffer the model
	model.buffer("models/sphere.obj");
	model.texture.load();
	return false;
}

void Engine::stop()
{
	shader.unload();
}

void Engine::update()
{
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

	//render the model
	model.texture.render();
	model.render();

	//swap the front and back buffers
	glfwSwapBuffers(window.pointer);
}
