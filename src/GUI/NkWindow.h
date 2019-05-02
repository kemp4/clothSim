#pragma once
#include"Options.h"

class NkWindow
{
public:
	NkWindow(GLFWwindow * window,Options*options);
	~NkWindow();
	void init();
	void update();
	void render();
private:
	struct nk_context *ctx;
	GLFWwindow* window;

	Options*options;
};

