#pragma once

class VaoObject
{
public:
	VaoObject();
	VaoObject(GLfloat * verticesArray, GLuint numberOfValues,bool normals);
	~VaoObject();
	void generate(GLfloat* verticesArray,GLuint numberOfValues);
	GLuint getID();
	GLuint getTrianglesNumber();
	void bind();
	std::string getName();
	void setName(std::string name);
private:
	std::string name;
	bool normals=false;
	GLuint id;
	GLuint verticlesNumber;
};