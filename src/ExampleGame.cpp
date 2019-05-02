#include <src/Objects/NonPlayerObject.h>
#include "baseHeader.h"
#include "ExampleGame.h"



ExampleGame::ExampleGame(GLFWwindow* window) : Game(window)
{

}

ExampleGame::~ExampleGame()
= default;

void ExampleGame::init() {

    Game::init();

    initRoad(1);
}







void ExampleGame::update()
{

    Game::update();
    if(options.paused) {

        newTime = std::clock();
        deltaTime = (double) (newTime - oldTime) / (double) CLOCKS_PER_SEC;
        oldTime = std::clock();
        fps = 1.0f / deltaTime;

        processInput();
        camera.update();

        glm::vec3 testD = glm::normalize(camera.getPos());


    }
}




void ExampleGame::initRoad(GLuint x)
{
    Shader* shader = ResourceManager::GetShader("shader1");
    cubesGroundX = x;
    cubesGroundY = 1;
    for (GLuint i = 0; i < cubesGroundX; i++) {
        for (GLuint j = 0; j < cubesGroundY; j++) {
            AbstractGameObject * someCube = new NonPlayerObject(glm::vec3(i*6, 0, j*6),shader, ResourceManager::GetTexture("texture3"), ResourceManager::getVAO("floor"));
            gameObjects.push_front(someCube);
        }
    }
}

void ExampleGame::processInput() {
    Game::processInput();
    if (keys[GLFW_KEY_LEFT]) {
        std::cout << "left key pressed\n";
    } else
    if(keys[GLFW_KEY_RIGHT]){
        std::cout << "right key pressed\n";
    }
}

