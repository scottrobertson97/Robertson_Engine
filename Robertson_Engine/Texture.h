#pragma once
#include <GL\glew.h>

class Texture
{
private:
	const char* filename = "textures/TestTexture.png";
	
	GLubyte* textureData;
	int imageWidth;
	int imageHeight;
public:
	GLuint texID;

	Texture();
	~Texture();

	void render();
	void unload();
	void load();
};

