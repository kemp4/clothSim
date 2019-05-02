#pragma once

#include <map>
#include <string>
#include <GL/glew.h>
#include "Texture.h"
#include "Shader.h"
#include "VaoObject.h"
#include <vector>

using namespace std;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static void loadShader(string vShaderFile, string fShaderFile, string name);

	static void loadShader(string vShaderFile, string fShaderFile,string gShaderFile, string name);

	static Shader* GetShader(std::string name);

	static Texture LoadTexture(const GLchar *file, GLboolean alpha, string name);
	static Texture GetTexture(std::string name);
	static VaoObject loadVAOFromFile(const GLchar *file, string = "", bool readNormals = false);

	static VaoObject loadVAO(GLfloat* verticesArray, GLuint numberOfValues,bool normals,string name);
	static VaoObject* getVAO(string name);

	static void deleteAssets();

	static unsigned int loadCubemap(vector<std::string> faces);
	static bool readWorld(std::string wordlName);
	static std::vector<std::string> GetTextureNames();
private:
	static map<string, Texture> textures;
	//collections
	static map<string, Shader> shaders;
	static map<string, VaoObject> vaos;
	static string readShaderFile(string filePath);
	static Texture loadTextureFromFile(const GLchar *file, GLboolean alpha);
	static glm::ivec3 strVertextoVec3(string s);
	static bool readAssets();
	static bool readShaders();
	static bool readVaos();
	static bool readTextures();
	static bool readObjects();

	static const string SHADERS_PATH;
};


