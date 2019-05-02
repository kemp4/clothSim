//
// Created by sk on 19.02.19.
//
#include "ParticleSystem.h"
#include "Particle.h"
//#include <list>

void ParticleSystem::update()
{
    if(nextParticleSpawnTime<clock()){
        spawnNewParticle();
    }
    std::list<AbstractGameObject *, std::allocator<AbstractGameObject *>>::iterator iterator;
    for (iterator = children.begin(); iterator != children.end(); ++iterator)
    {
        if (Particle* particle = dynamic_cast<Particle*>(*iterator))
        {
            if(!particle->isAlive()) {
                delete *iterator;
                iterator = children.erase(iterator);
            }
        }
    }
}
ParticleSystem::ParticleSystem(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao):SimpleObject(position, shader,  texture, vao)
{
    visible = false;
    nextParticleSpawnTime = clock();
}

void ParticleSystem::spawnNewParticle() {
//    std::cout << "particle spawned\n";
    for (int i = 0 ; i < particlesNumPerSpawn ; i++) {
        AbstractGameObject *newParticle = new Particle(getPosition(), shader, texture, vao);
        children.push_back(newParticle);
    }
    nextParticleSpawnTime = static_cast<clock_t>(clock() + CLOCKS_PER_SEC * 0.001f);
}
