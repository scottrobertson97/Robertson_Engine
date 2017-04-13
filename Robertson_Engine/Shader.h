#pragma once
#include <GL\glew.h>
#include <string>
#include <iostream>
#include <fstream>
using std::ifstream;
using std::string;
class Shader
{
private:
	GLuint program, vprogram, fprogram;
	string filenamev = "shaders/vshader.glsl";
	string filenamef = "shaders/fshader.glsl";
public:
	Shader();
	virtual ~Shader();

	bool load();
	bool compile(GLenum shaderType, GLuint &shaderProgram);
	void use();
	void unload();
	GLuint getProgram();
};

