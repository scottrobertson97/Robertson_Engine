#include "Engine.h"

Timer Engine::timer;
Window Engine::window;
Camera Engine::camera;

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
	if (!window.start(width, height))
		return false;
	camera.start();

	//change color of the window
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	bufferModels();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (!shader.load())
	{
		glfwTerminate();
	}
	
	shader.use();

	return true;
}

bool Engine::bufferModels()
{
	model.buffer("models/teapot.obj");
	return false;
}

void Engine::stop()
{	
}

void Engine::update()
{
	//get inputs
	
	timer.update();
	system("cls");

	camera.update();
}

void Engine::draw()
{
	//clear the canvas
	glClear(GL_COLOR_BUFFER_BIT);

	model.render();

	//swap the front and back buffers
	glfwSwapBuffers(window.pointer);
}
