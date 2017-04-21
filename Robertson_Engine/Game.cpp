#include "Engine.h"

int main()
{
	//try to start the endine with a window size
	if (!Engine::start(800, 600))
		return -1;

	/*Game Loop*/
	while (!glfwWindowShouldClose(Engine::window.pointer))
	{
		//get key events
		glfwPollEvents();

		//break the loop if the user presses ESC
		if (glfwGetKey(Engine::window.pointer, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			break;

		//update then draw the engine
		Engine::update();
		Engine::draw();
	}

	Engine::stop();
	glfwTerminate();
	return 0;
}