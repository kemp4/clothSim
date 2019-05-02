#pragma once

#include "baseHeader.h"
#include"Game.h"
#include "src/ExampleGame.h"

GLfloat lastMouseX = 400;
GLfloat lastMouseY = 300;

Game* game;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			game->setKey(key) ;
		else if (action == GLFW_RELEASE)
		{
			game->clearKey(key);
			//game.KeysProcessed[key] = GL_FALSE;
		}
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	game->changeCameraDirection(lastMouseX-xpos, lastMouseY-ypos);
	lastMouseX = (GLfloat)xpos;
	lastMouseY = (GLfloat)ypos;

}

GLFWwindow* createWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "game", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	return window;
}
