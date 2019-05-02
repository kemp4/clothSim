//
// Created by sk on 19.02.19.
//

#ifndef GKP_PARTICLE_H
#define GKP_PARTICLE_H


#include <src/Objects/SimpleObject.h>

class Particle :public SimpleObject {
public:
    Particle(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao);
    void update() override;
    bool isAlive();
protected:
    glm::vec3 velocity;
    clock_t particleDeathTime;
    bool alive;
};


#endif //GKP_PARTICLE_H
