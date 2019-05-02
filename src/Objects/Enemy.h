//
// Created by sk on 18.02.19.
//

#ifndef GKP_ENEMY_H
#define GKP_ENEMY_H


#include "SimpleObject.h"

class Enemy : public SimpleObject{
public:
    Enemy(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao);
    void update() override;
protected:
    float lenght = 5;
};


#endif //GKP_NONPLAYEROBJECT_H
