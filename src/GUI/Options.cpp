#include "src/baseHeader.h"
#include "Options.h"


Options::Options()
{
	paused = true;
	ambientColor = glm::vec3(200, 200, 200);
	ambientStrength = 0.7;
	points = 0;
}


Options::~Options()
{
}

