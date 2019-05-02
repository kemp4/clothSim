//
// Created by sk on 19.02.19.
//

#ifndef GKP_PARTICLESYSTEM_H
#define GKP_PARTICLESYSTEM_H


#include <src/Objects/SimpleObject.h>
#include <time.h>
class ParticleSystem:public SimpleObject {
public:
    ParticleSystem(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao);
    void update() override;

protected:

    int maxParticles =100;
    clock_t nextParticleSpawnTime;
    void spawnNewParticle();
    int particlesNumPerSpawn = 3;
};


#endif //GKP_PARTICLESYSTEM_H
