#pragma once
#include <GL\glew.h>

class Texture
{
private:
	const char* filename = "textures/TestTexture.png";
	GLuint texID;
	GLubyte* textureData;
	int imageWidth;
	int imageHeight;
public:
	Texture();
	~Texture();

	void render();
	void unload();
	void load();
};

