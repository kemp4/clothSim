//
// Created by sk on 18.02.19.
//

#include "Enemy.h"

void Enemy::update()
{
    move(glm::vec3(-0.1,0,0));
    if (getPosition().x<=-7){
        std::cout <<  "problems with deleting garbage\n";
    }
}
Enemy::Enemy(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao):SimpleObject(position, shader,  texture, vao)
{

}

