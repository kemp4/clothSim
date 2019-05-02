#pragma once

#include <random>
#include "Game.h"
#include <src/Objects/Enemy.h>
#include <src/Objects/Particle/ParticleSystem.h>

class ExampleGame :
	public Game
{
public:
	explicit ExampleGame(GLFWwindow* window);
	~ExampleGame();
	virtual void init();
	static int points ;
protected:

	void processInput() override;
	void update() override;
    void initRoad(GLuint x);

};

