#include <utility>

#include "src/baseHeader.h"
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <vector>
#include "SOIL.h"

const string ResourceManager::SHADERS_PATH = "shaders/";

ResourceManager::ResourceManager()
{

}


ResourceManager::~ResourceManager()
{
}


void ResourceManager::loadShader(string vShaderFile, string fShaderFile, string gShaderFile,string name)
{
	try {
		// reading shaders from files
		string vsCodeStr = readShaderFile(std::move(vShaderFile));
		string fsCodeStr = readShaderFile(std::move(fShaderFile));
		string gsCodeStr = readShaderFile(std::move(gShaderFile));
		// converting strings to c strings
		const GLchar *vsCodeCstr = vsCodeStr.c_str();
		const GLchar *fsCodeCstr = fsCodeStr.c_str();
		const GLchar *gsCodeCstr = gsCodeStr.c_str();
		Shader shader;
		shader.compile(vsCodeCstr, fsCodeCstr,gsCodeCstr);
		shaders[name] = shader;
	}
	catch (exception e) {
		throw e;
	}
}

void ResourceManager::loadShader(string vShaderFile, string fShaderFile, string name)
{
	try {
		// reading shaders from files
		string vsCodeStr = readShaderFile(vShaderFile);
		string fsCodeStr = readShaderFile(fShaderFile);
		// converting strings to c strings
		const GLchar *vsCodeCstr = vsCodeStr.c_str();
		const GLchar *fsCodeCstr = fsCodeStr.c_str();
		Shader shader;
		shader.setName(name);
		shader.compile(vsCodeCstr, fsCodeCstr);
		shaders[name] = shader;
	}
	catch (exception e) {
		throw e;
	}
}

Shader* ResourceManager::GetShader(std::string name)
{
	return &shaders[name];
}

Texture ResourceManager::LoadTexture(const GLchar * file, GLboolean alpha, string name)
{
	char path[256];
	char *pre = const_cast<char *>("assets/textures/");
	sprintf(path, "%s%s", pre, file);
	Texture text = loadTextureFromFile(path, alpha);
	text.setName(name);
	textures[name] = text;
	
	return textures[name];
}

Texture ResourceManager::GetTexture(std::string name)
{
	return textures[name];
}

VaoObject ResourceManager::loadVAOFromFile(const GLchar * file,string name,bool readNormals )
{
	char path[256];
	char *pre = const_cast<char *>("assets/objects/");
	std::vector < glm::vec3* > vertices;
	std::vector < glm::vec3* > normals;
	std::vector < glm::vec2* > textureCords;
	std::vector < string* > faces;
	sprintf(path, "%s%s", pre, file);
	//string objinfo = readShaderFile(path);
	//bool readNormals = false;
	std::ifstream infile(path);
	string line;
	float x, y, z;
	bool read=true;
	while (infile >> line )
	{

		//std::cout << line<<std::endl;
		//comment
		if (line == "#") {	
			std::getline(infile, line);
		}
		// object name
		else if ((line == "o")&&(name.empty())) {
			std::getline(infile, name);
		}
		// vertex
		else if (line == "v") {
			infile >> x >> y >> z;
			glm::vec3 * vertexPos = new glm::vec3(x,y,z);
			vertices.push_back(vertexPos);
		}
		// texture cords
		else if (line == "vt") {
			infile >> x >> y;
			glm::vec2 * texturePos= new glm::vec2(x, y);
			textureCords.push_back(texturePos);
		}
		// vertex normal
		else if (line == "vn") {
			infile >> x >> y >> z;
			glm::vec3 * vertexNormal = new glm::vec3(x, y, z);
			normals.push_back(vertexNormal);
		}
		// face
		else if (line == "f") {
			// not optimal way
			string * vinf = new string[3];
			infile >> vinf[0] >> vinf[1] >> vinf[2];
			faces.push_back(vinf);
		}
	}

	int stride;
	if (!readNormals) {
		stride = 5;
	}
	else {
		stride = 8;
	}
	int vertexInfoFloats = 3 * stride;						 // 3 vertices per face
	int vertexSize = sizeof(GLfloat)*vertexInfoFloats;
	int numberOfVertices = vertexInfoFloats*faces.size();
	GLfloat * result = (GLfloat*)malloc(vertexSize*faces.size());
	while (faces.size() != 0) {
		int index = faces.size()-1;
		string * face = faces[index];
		glm::ivec3 vertex;
		for (int i = 0; i < 3; i++) {						  // 3 vertices per face
			vertex = strVertextoVec3(face[i]);
			//setting vao values
			result[index*vertexInfoFloats + 0 + stride * i] = vertices[vertex.x-1]->x;
			result[index*vertexInfoFloats + 1 + stride * i] = vertices[vertex.x-1]->y;
			result[index*vertexInfoFloats + 2 + stride * i] = vertices[vertex.x-1]->z;
			result[index*vertexInfoFloats + 3 + stride * i] = textureCords[vertex.y-1]->x;
			result[index*vertexInfoFloats + 4 + stride * i] = textureCords[vertex.y-1]->y;

			if (readNormals == true) {
				result[index*vertexInfoFloats + 5 + stride * i] = normals[vertex.z - 1]->x;
				result[index*vertexInfoFloats + 6 + stride * i] = normals[vertex.z - 1]->y;
				result[index*vertexInfoFloats + 7 + stride * i] = normals[vertex.z - 1]->z;
			}
		}
		delete[] face;
		faces.pop_back();
	}
	return loadVAO(result, numberOfVertices,readNormals,name);
}

VaoObject ResourceManager::loadVAO(GLfloat * verticesArray, GLuint numberOfValues,bool normals,string name)
{
	VaoObject vao =VaoObject(verticesArray, numberOfValues, normals);
	vao.setName(name);
	vaos[name] = vao;//VaoObject( verticesArray, numberOfValues,normals);
	return vaos[name];
}

VaoObject* ResourceManager::getVAO(string name)
{
	return &vaos[name];
}

void ResourceManager::deleteAssets()
{
	for (auto it = shaders.cbegin(); it != shaders.cend();) {
		shaders.erase(it++);
	}
	for (auto it = vaos.cbegin(); it != vaos.cend();) {
		vaos.erase(it++);
	}
	for (auto it = textures.cbegin(); it != textures.cend();) {
		textures.erase(it++);
	}
}

string ResourceManager::readShaderFile(string filePath)
{

	ifstream file (SHADERS_PATH+filePath);
	stringstream fileStream;
	fileStream << file.rdbuf();
	file.close();
	return fileStream.str();
}

Texture ResourceManager::loadTextureFromFile(const GLchar * file, GLboolean alpha)
{
	Texture texture;
	if (alpha)
	{
		texture.setIntFormat(GL_RGBA);
		texture.setImgFormat(GL_RGBA);
	}
	// Load image
	int width, height;
	unsigned char* img;
	if (texture.getImgFormat() == GL_RGBA) {
		img = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGBA );
	}
	else {
		img = SOIL_load_image(file, &width, &height, 0, SOIL_LOAD_RGB);
	}
	// Now generate texture
	texture.Generate(width, height, img);
	// And finally free image data
	SOIL_free_image_data(img);
	return texture;
}

glm::ivec3 ResourceManager::strVertextoVec3(string s)
{
	int vinf[] = {0,0,0};
	int index=0;
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 47) {
			index++;
		}else{
			vinf[index] = vinf[index] * 10 + (s[i] - '0');
		}
	}
	return glm::ivec3(vinf[0],vinf[1],vinf[2]);
}




 unsigned int ResourceManager::loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		faces[i]= "assets/textures/skybox/"+faces[i] ;
		const GLchar *filename = faces[i].c_str();
		unsigned char *data = SOIL_load_image(filename, &width, &height, &nrChannels, SOIL_LOAD_RGB);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			SOIL_free_image_data(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			SOIL_free_image_data(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

 bool ResourceManager::readWorld(std::string wordlName)
 {
	 return false;
 }

 std::vector<std::string> ResourceManager::GetTextureNames()
 {
	 std::vector<std::string> result;
	 for (auto it = textures.begin(); it != textures.end(); ++it)
	 {
		 result.push_back(it->second.getName());
	 }
	 return result;
 }

 bool ResourceManager::readAssets()
 {
	 if(readShaders())
		if(readVaos())
			if(readTextures())
				return true;
				
	 return false;
 }
 bool ResourceManager::readShaders()
 {
	 return false;
 }

 bool ResourceManager::readVaos()
 {
	 return false;
 }

 bool ResourceManager::readTextures()
 {
	 return false;
 }

 bool ResourceManager::readObjects()
 {
	 return false;
 }
