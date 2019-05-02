#pragma once
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <list>
#include"src/Objects/SimpleObject.h"
#include"src/Objects/AbstractGameObject.h"
#include"src/Objects/Camera.h"
#include<stdlib.h>
#include"src/GUI/NkWindow.h"
#include"src/ResoureManagment/ResourceManager.h"
#include"src/GUI/Options.h"


class Game
{
public:
	Game(GLFWwindow* window);
	~Game();

	virtual void startMainGameLoop();

	void setKey(int keyIndex);
	void clearKey(int keyIndex);
	void changeCameraDirection(GLfloat x,GLfloat y);
	virtual void init();

private:
	void initSkybox();
	void loadModels() const;
    void loadTextures() const;
protected:
	Options options;

	virtual  void update();
	virtual void render();
	virtual void processInput();
	void exitGame();

	GLboolean  keys[1024] = {GL_FALSE};
	GLFWwindow* window;
	Camera camera;
	std::list<AbstractGameObject*> gameObjects;

	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	std::clock_t  oldTime;
	std::clock_t newTime;
	double deltaTime=0;
	double fps;



	// gui
	NkWindow* mainWindow;

	struct nk_context *ctx;
	glm::vec3 lightColor;
	float ambientStrength;

	AbstractGameObject * rayTest;

	GLint lcLoc;
	GLint lpLoc;
	GLint vpLoc;

	GLfloat minimalAngle = 3.1f;
	void renderObjects();
	bool delCube;
	GLuint cubesGroundX;
	GLuint cubesGroundY;

	Shader* skyboxShader;
	unsigned int cubemapTexture;

	void deleteObjects();
;
	GLfloat skybox[180] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	void drawGameObjectWithChildren(AbstractGameObject *&gameObject);

	void updateObjects();

	void updateGameObjectWithChildren(AbstractGameObject *&gameObject);
};

