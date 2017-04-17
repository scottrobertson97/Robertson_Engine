#include "Texture.h"



Texture::Texture()
{
}


Texture::~Texture()
{
}

void Texture::render()
{
	
}

void Texture::unload()
{
	glDeleteTextures(1, &texID);
}

void Texture::load()
{
	//get the image's format
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(filename, 0);
	//load image into a bitmap
	FIBITMAP* bitmap = FreeImage_Load(format, filename);
	//get bits per pixel
	int bitsPerPixel = FreeImage_GetBPP(bitmap);

	FIBITMAP* bitmap32;
	if (bitsPerPixel == 32)
		bitmap32 = bitmap;
	else
		bitmap32 = FreeImage_ConvertTo32Bits(bitmap);

	imageWidth = FreeImage_GetWidth(bitmap32);
	imageHeight = FreeImage_GetHeight(bitmap32);

	//get the data as a array of bytes
	textureData = FreeImage_GetBits(bitmap32);

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexImage2D(GL_TEXTURE_2D,    // Type of texture
		0,                // Mipmap level (0 being the top level i.e. full size)
		GL_RGBA,          // Internal format
		imageWidth,       // Width of the texture
		imageHeight,      // Height of the texture,
		0,                // Border in pixels
		GL_BGRA,          // Data format
		GL_UNSIGNED_BYTE, // Type of texture data
		textureData);     // The image data to use for this texture

	//https://r3dux.org/2014/10/how-to-load-an-opengl-texture-using-the-freeimage-library-or-freeimageplus-technically/
}
