#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <glm\gtx\transform.hpp>
using glm::vec3;
using glm::vec2;

struct Vertex
{
	vec3 location;
	vec2 uv;
	vec3 normal;
};
struct VertInd
{
	unsigned int locInd, unInd, normInd;
};
class Model
{
private:
	GLuint vertArr;
	unsigned int vertCount;
public:
	Model();
	~Model();

	bool buffer(std::string objFile);
	void render();
};

