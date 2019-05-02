#pragma once
#include<vector>

class Options
{
public:
	Options();
	~Options();

	bool paused;
	bool save=false;
	bool load=false;


	float ambientStrength;
	glm::vec3 ambientColor;

	int points;

    bool gameOver=false;
};

