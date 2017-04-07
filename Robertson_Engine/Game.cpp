#include "Engine.h"

int main()
{
	if (!Engine::start(1200, 720))
		return -1;

	//Shader shader;
	//GLuint vertArr;
	//GLuint vertBuf;
	//unsigned int vertCount;
	//
	////create quad vertex data
	//vector<glm::vec3> locs = {
	//	{ .9, .9,0 },
	//	{ -.9, .9,0 },
	//	{ -.9,-.9,0 },
	//	{ .9,-.9,0 } };
	////conect the dots
	//vector<unsigned int> locInds = {
	//	0,1,2,
	//	0,2,3 };
	//
	//vertCount = locInds.size();
	//
	////process model data
	////vert buff data contains the points in the correct order
	////triangles are drawn counter clockwise
	//vector <glm::vec3> vertBufData(vertCount);
	//for (unsigned int i = 0; i < vertCount; i++)
	//	vertBufData[i] = locs[locInds[i]];
	//


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