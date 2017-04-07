#include "Engine.h"
#include "Model.h"

Model::Model()
{
	vertArr = 0;
	vertCount = 0;
}

Model::~Model()
{
}

bool Model::buffer(std::string objFile)
{
	std::vector<vec3> locations;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	std::vector<unsigned int> vertInds;

	std::ifstream obj(objFile);
	if (!obj.is_open)
		return false;

	std::string line;

	while (std::getline(obj, line))
	{
		std::stringstream ss(line);
	}

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

	return false;
}

void Model::render()
{
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);
}
