#include "Engine.h"

int main()
{
	if (!Engine::start(1200, 720))
		return -1;

	while (!glfwWindowShouldClose(Engine::window.pointer))
	{
		Engine::update();
		Engine::draw();
		glfwPollEvents();
	}

	Engine::stop();

	glfwTerminate();
	return 0;
}