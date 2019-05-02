#include "src/baseHeader.h"
#include "Shader.h"


Shader::Shader()
{
	this->id = NULL;
}


Shader::~Shader()
{
}

GLuint Shader::getID()
{
	return id;
}

void Shader::compile(const GLchar * vsSource, const GLchar * fsSource, const GLchar *gsSource)
{

	this->id = glCreateProgram();
	GLuint vsID;
	GLuint fsID;
	GLuint gsID;
	vsID = glCreateShader(GL_VERTEX_SHADER);
	fsID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vsID, 1, &vsSource, nullptr);
	glShaderSource(fsID, 1, &fsSource, nullptr);
	glCompileShader(vsID);
	checkCompileErrors(vsID, "VERTEX");
	glCompileShader(fsID);
	checkCompileErrors(fsID, "FRAGMENT");
//    std::cout <<  "\""<<gsSource<<"\"" << "\n";

	if  (strcmp(gsSource,"")!=0) {
		
		gsID = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gsID, 1, &vsSource, nullptr);
		glCompileShader(gsID);
		checkCompileErrors(gsID, "GEOMETRY");
		glAttachShader(this->id, gsID);
		glAttachShader(this->id, fsID);
		glAttachShader(this->id, vsID);
		glLinkProgram(this->id);
		checkCompileErrors(this->id, "PROGRAM");
		glDeleteShader(gsID);
	}
	else {
		glAttachShader(this->id, fsID);
		glAttachShader(this->id, vsID);
		glLinkProgram(this->id);
		checkCompileErrors(this->id, "PROGRAM");
	}

	//glUseProgram(this->id);
	glDeleteShader(vsID);
	glDeleteShader(fsID);

}
Shader & Shader::use()
{
	glUseProgram(this->id);
	return *this;
}

std::string Shader::getName()
{
	return name;
}

void Shader::setName(std::string name)
{
	this->name = name;
}


void Shader::checkCompileErrors(GLuint object, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, nullptr, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
				
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, nullptr, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}
