#include "Engine.h"

int main()
{
	if (!Engine::start(1200, 720))
		return -1;

	//Shader shader;

	///*shader*/
	//if (!shader.load())
	//{
	//	glfwTerminate();
	//}
	//
	//shader.use();

	/*Game Loop*/
	while (!glfwWindowShouldClose(Engine::window.pointer))
	{
		Engine::update();

		Engine::draw();
		glfwPollEvents();
	}

	//shader.unload();
	Engine::stop();

	glfwTerminate();
	return 0;
}