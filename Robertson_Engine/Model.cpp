#include "Engine.h"
#include "Model.h"

Model::Model()
{
	vertArr = 0;
	vertBuf = 0;
	vertCount = 0;

	scale = 1.f;
}

Model::~Model()
{
}

bool Model::buffer(std::string objFile)
{
	printf("buffer model");
	std::vector<vec3> locations;
	std::vector<vec2> uvs;
	std::vector<vec3> normals;
	std::vector<VertInd> vertInds;

	//try to open the onj file
	std::ifstream obj(objFile);
	if (!obj.is_open())
	{
		printf("could not loat the model file");
		return false;
	}

	//string to hold each line of the file
	std::string line;

	//iterate through the file getting each line
	while (std::getline(obj, line))
	{
		std::stringstream ss(line);

		std::string label;

		ss >> label;

		//load the position data
		if (label == "v")
		{
			vec3 loc;
			ss >> loc.x >> loc.y >> loc.z;
			locations.push_back(loc);
		}
		//load the uv data
		else if (label == "vt")
		{
			vec2 uv;
			ss >> uv.x >> uv.y;
			uvs.push_back(uv);
		}
		//load the norm data
		else if (label == "vn")
		{
			vec3 norm;
			ss >> norm.x >> norm.y >> norm.z;
			normals.push_back(norm);
		}
		//load the vertex data
		else if (label == "f")
		{
			unsigned int i;
			char slash;
			for (int j = 0; j < 3; j++)
			{
				VertInd vind;
				ss >> i >> slash;
				vind.locInd = i - 1;
				ss >> i >> slash;
				vind.uvInd = i - 1;
				ss >> i;
				vind.normInd = i - 1;

				vertInds.push_back(vind);
			}
		}
	}

	//close the file
	obj.close();

	vertCount = vertInds.size();

	std::vector <Vertex> vertBufData(vertCount);

	//fill the vertBufData with data
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i] = 
		{	
			locations[vertInds[i].locInd] * scale,
			uvs[vertInds[i].uvInd],
			normals[vertInds[i].normInd]
		};
	}

	//generate array and buffer
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	//bind to the buffer
	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);
	
	//storing the data in the buffer
	glBufferData(
		GL_ARRAY_BUFFER,			//where to copy
		sizeof(Vertex) * vertCount,	//# of bytes to copy
		&vertBufData[0],			//where to copy from
		GL_STATIC_DRAW);			//"hint" to opengl

	/*Setting the position attribute*/
	//describe the buffer layout
	//enable the attribute
	glEnableVertexAttribArray(0);	//attribute index =0

	//set up the attribute
	glVertexAttribPointer
	(
		0,				//attribute index
		3,				//number of componets(x,y,z)
		GL_FLOAT,		//type of data
		GL_FALSE,		//should we nomalize data?
		sizeof(Vertex),	//stride(bytes per vertex)
		0				//offset to this attribute
	);				

	/*setting the uv attribute*/
	glEnableVertexAttribArray(1);	//attribute index =1
									//set up the attribute
	glVertexAttribPointer
	(
		1,						//attribute index
		2,						//number of componets(x,y)
		GL_FLOAT,				//type of data
		GL_FALSE,				//should we nomalize data?
		sizeof(Vertex),			//stride(bytes per vertex)
		(void *)(sizeof(vec3))	//offset to this attribute
	);				
	
	/*setting the normal attribute*/
	glEnableVertexAttribArray(2);	//attribute index =2
									//set up the attribute
	glVertexAttribPointer
	(
		2,										//attribute index
		3,										//number of componets(x,y,z)
		GL_FLOAT,								//type of data
		GL_FALSE,								//should we nomalize data?
		sizeof(Vertex),							//stride(bytes per vertex)
		(void *)(sizeof(vec3) + sizeof(vec2))	//offset to this attribute
	);				

	//unbind when finished editing
	glBindVertexArray(0);

	return false;
}

void Model::bind()
{
	glBindVertexArray(vertArr);
}

void Model::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);
}
