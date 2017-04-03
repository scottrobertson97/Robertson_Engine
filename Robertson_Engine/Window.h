#pragma once
#include <GLFW\glfw3.h>

class Window
{
private:
	
public:
	Window();
	~Window();

	GLFWwindow* pointer;
	int width;
	int height;

	int halfWidth;
	int halfHeight;

	bool start(int width, int height);
};

