#include "src/baseHeader.h"
#include "VaoObject.h"


VaoObject::VaoObject()
{
}
VaoObject::VaoObject(GLfloat * verticesArray, GLuint numberOfValues,bool normals)
{
	this->normals = normals;
	generate( verticesArray,  numberOfValues);
}


VaoObject::~VaoObject()
{
}

void VaoObject::generate(GLfloat * verticesArray, GLuint numberOfValues)
{
	GLuint VBO;
	GLuint stride = 5;
	verticlesNumber = numberOfValues;
	glGenVertexArrays(1, &id);
	glGenBuffers(1, &VBO);
	glBindVertexArray(id);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, numberOfValues* sizeof(GLfloat), verticesArray, GL_STATIC_DRAW);
	if (normals) {
		stride = 8;
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	if (normals) {
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride * sizeof(GLfloat), (GLvoid*)(5 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}


	glBindVertexArray(0);
}

GLuint VaoObject::getID()
{
	return id;
}

GLuint VaoObject::getTrianglesNumber()
{
	if (!normals) {
		return verticlesNumber / 5;
	}else
		return verticlesNumber / 8;
}


void VaoObject::bind()
{
	glBindVertexArray(getID());
}

std::string VaoObject::getName()
{
	return name;
}

void VaoObject::setName(std::string name)
{
	this->name = name;
}
