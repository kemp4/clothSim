#include "src/baseHeader.h"
#include "Texture.h"


Texture::Texture()
{
	glGenTextures(1, &this->id);
}


Texture::~Texture()
{
}

void Texture::Generate(GLuint width, GLuint height, unsigned char * data)
{
	this->width = width;
	this->height = height;
	// Create Texture
	glBindTexture(GL_TEXTURE_2D, this->id);
	glTexImage2D(GL_TEXTURE_2D, 0, this->intFormat, width, height, 0, this->imgFormat, GL_UNSIGNED_BYTE, data);
	// Set Texture wrap and filter modes
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
	glGenerateMipmap(GL_TEXTURE_2D);
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture::setImgFormat(GLuint imgFormat)
{
	this->imgFormat = imgFormat;
}

void Texture::setIntFormat(GLuint intFormat)
{
	this->intFormat = intFormat;
}

GLuint Texture::getImgFormat()
{
	return imgFormat;
}

GLuint Texture::getIntFormat()
{
	return intFormat;
}

GLuint Texture::getID()
{
	return id;
}

std::string Texture::getName()
{
	return name;
}

void Texture::setName(std::string name)
{
	this->name = name;
}
