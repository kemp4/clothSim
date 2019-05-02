//
// Created by sk on 19.02.19.
//

#include "Particle.h"

void Particle::update() {
    SimpleObject::update();
    move(velocity);
    alive = particleDeathTime>clock();
//    if (!alive){
//        visible=false;
//    }

}

Particle::Particle(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao):SimpleObject(position, shader,  texture, vao)
{
    visible = true;
    auto randX = (0.2 - (float)(rand() % 20) / 10)*0.2;
    auto randY = ((float)(rand() % 20) / 100);
    auto randZ = (0.1 - (float)(rand() % 20) / 100)*0.3;
    velocity = glm::vec3(randX,randY,randZ);
    particleDeathTime = static_cast<clock_t>(rand()%10 * CLOCKS_PER_SEC * 0.004f + clock());
    alive=true;
}
bool Particle::isAlive(){
    return alive;
}