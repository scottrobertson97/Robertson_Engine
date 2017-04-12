#include "Shader.h"
#include <vector>

Shader::Shader()
{
}

Shader::~Shader()
{
}

bool Shader::load()
{
	//try to compile the shaders
	if (compile(GL_VERTEX_SHADER, vprogram) && compile(GL_FRAGMENT_SHADER, fprogram) == false)
	{
		return false;
	}

	//create the program
	program = glCreateProgram();
	//attack shaders and link
	glAttachShader(program, vprogram);
	glAttachShader(program, fprogram);
	glLinkProgram(program);
	
	/*check if linked*/
	GLint result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if (result != GL_TRUE) 
	{
		//get the error log and store it
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<GLchar> log(logLength);
		glGetProgramInfoLog(program, logLength, &logLength, &log[0]);
		//delte program
		glDeleteProgram(program);
		return false;
	}

	return true;
}

bool Shader::compile(GLenum shaderType, GLuint &shaderProgram)
{
	/*Loading shader*/
	//get the right shader type
	string filename;
	if (shaderType == GL_VERTEX_SHADER)
		filename = filenamev;
	else if (shaderType == GL_FRAGMENT_SHADER)
		filename = filenamef;

	//open shader file
	ifstream is(filename, std::ios::binary);
	//check if it opened
	if (!is.is_open())
	{
		printf("unable to load shader file");
		return false;
	}
	//get the length of the file
	is.seekg(0, std::ios::end);
	int length = (int)is.tellg();
	is.seekg(0, std::ios::beg);
	//get the code in the shader
	char* source = new char[length + 1];
	is.read(source, length);
	source[length] = '\0';
	//close shader
	is.close();

	//create shader
	shaderProgram = glCreateShader(shaderType);
	//set the source
	glShaderSource(shaderProgram, 1, &source, 0);
	//compile
	glCompileShader(shaderProgram);
	//get complie status
	GLint result;
	glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &result);
	//if the shader didnt compile
	if (result != GL_TRUE)
	{
		//get log length
		GLint logLength = 0;
		glGetShaderiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
		//vector to hold log
		std::vector<GLchar> log(logLength);
		//get log
		glGetShaderInfoLog(shaderProgram, logLength, &logLength, &log[0]);
		//delete shader
		glDeleteShader(shaderProgram);
		shaderProgram = 0;
		delete[] source;
		return false;
	}

	delete[] source;
	return true;
}

void Shader::use()
{
	glUseProgram(program);

	//light loaction
	int lightLoc = glGetUniformLocation(program, "lightLoc");
	glUniform3f(lightLoc, 0, 20, 0);

	//light loaction
	int cameraLoc = glGetUniformLocation(program, "cameraLoc");
	glUniform3f(cameraLoc, 0, 20, 0);
}

void Shader::unload()
{
	//delete the programs
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);
	program = 0;
	vprogram = 0;
	fprogram = 0;
}
