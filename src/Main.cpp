#include "baseHeader.h"
#include"Main.h"

static void error_callback(int e, const char *d)
{
	printf("Error %d: %s\n", e, d);
}

int main()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stdout, "[GFLW] failed to init!\n");
		exit(1);
	}
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = createWindow();//glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo", NULL, NULL);
	if (window != NULL) {

		//game = new Game(window);
		game = new ExampleGame(window);
		game->init();
		game->startMainGameLoop();
	}
	else {

		return -1;
	}
	delete(game);
	return 0;
}

