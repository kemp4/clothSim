//
// Created by sk on 18.02.19.
//

#include "NonPlayerObject.h"
void NonPlayerObject::update()
{
    move(glm::vec3(-0.1,0,0));
    if (getPosition().x<=-6){
        setPosition(glm::vec3(lenght*5.98, 0, getPosition().z));
    }
}
NonPlayerObject::NonPlayerObject(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao):SimpleObject(position, shader,  texture, vao)
{

}

