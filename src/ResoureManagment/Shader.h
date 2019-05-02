#pragma once
#include<iostream>
#include<string>

class Shader
{
public:
	Shader();
	~Shader();
	uint getID();
	void compile(const char *vsSource, const char *fsSource, const char *gsSource="");
	Shader  &use();
	std::string getName();
	void setName(std::string name);
private:
	std::string name;
	uint id;
	void checkCompileErrors(uint object, std::string type);
};

