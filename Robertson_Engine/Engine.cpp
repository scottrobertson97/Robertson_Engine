#include "Engine.h"

Timer Engine::timer;
Window Engine::window;
Camera Engine::camera;

Shader shader;
GLuint vertArr;
GLuint vertBuf;
unsigned int vertCount;

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

	//create quad vertex data
	vector<glm::vec3> locs = {
		{ .9, .9,0 },
		{ -.9, .9,0 },
		{ -.9,-.9,0 },
		{ .9,-.9,0 } };
	//conect the dots
	vector<unsigned int> locInds = {
		0,1,2,
		0,2,3 };

	vertCount = locInds.size();

	//process model data
	//vert buff data contains the points in the correct order
	//triangles are drawn counter clockwise
	vector <glm::vec3> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
		vertBufData[i] = locs[locInds[i]];


	/*shader*/
	if (!shader.load())
	{
		glfwTerminate();
	}

	shader.use();

	/*should be in a model class*/
	//generationg a buffer
	
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);
	//bind to the buffer
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	//storing the data in the buffer
	glBufferData(
		GL_ARRAY_BUFFER,				//where to copy
		sizeof(glm::vec3) * vertCount,	//# of bytes to copy
		&vertBufData[0],				//where to copy from
		GL_STATIC_DRAW);				//"hint" to opengl
										//describe the buffer layout
										//enable the attribute
	glEnableVertexAttribArray(0);	//attribute index =0
									//set up the attribute
	glVertexAttribPointer(
		0,					//attribute index
		3,					//number of componets(x,y,z)
		GL_FLOAT,			//type of data
		GL_FALSE,			//should we nomalize data?
		sizeof(glm::vec3),	//stride(bytes per vertex)
		0);					//offset to this attribute
							//unbind when finished editing
	glBindVertexArray(0);

	//change color of the window
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	return true;
}

void Engine::stop()
{
	shader.unload();
}

void Engine::update()
{
	//get inputs
	glfwPollEvents();
	timer.update();
	system("cls");

	camera.update();
}

void Engine::draw()
{
	//clear the canvas
	glClear(GL_COLOR_BUFFER_BIT);

	//draw the triangles
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);

	//swap the front and back buffers
	glfwSwapBuffers(window.pointer);
}
