#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <FreeImage.h>

#include <iostream>
#include <vector>
using std::vector;

#include "Shader.h"
#include "Camera.h"
#include "Window.h"
#include "Timer.h"
#include "Model.h"

class Engine
{
public:
	Engine();
	~Engine();

	static Timer timer;
	static Window window;
	static Camera camera;

	static bool start(int width, int height);
	static bool bufferModels();

	static void stop();
	static void update();
	static void draw();
};
