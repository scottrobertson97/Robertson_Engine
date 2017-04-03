#include "Engine.h"
#include "Window.h"

Window::Window()
{
}


Window::~Window()
{
}

bool Window::start(int width, int height)
{
	this->width = width;
	this->height = height;

	halfWidth = width/2;
	halfHeight = height / 2;

	//initialize window library
	if (glfwInit() == GL_FALSE)
	{
		glfwTerminate();
		return false;
	}
	//create a window moded window
	pointer = glfwCreateWindow(width, height, "Robertson DSA1 Engine", NULL, NULL);

	////make it the currently active window or quit
	if (pointer != nullptr)
	{
		glfwMakeContextCurrent(pointer);
	}
	else
	{
		glfwTerminate();
		return false;
	}

	//initialize GLEW or quit
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	return true;
}
