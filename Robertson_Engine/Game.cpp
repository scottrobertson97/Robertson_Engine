#include "Engine.h"

int main()
{
	if (!Engine::start(800, 600))
		return -1;

	while (!glfwWindowShouldClose(Engine::window.pointer))
	{
		Engine::update();
		Engine::draw();
	}

	Engine::stop();

	glfwTerminate();
	return 0;
}