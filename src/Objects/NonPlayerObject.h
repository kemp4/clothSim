//
// Created by sk on 18.02.19.
//

#ifndef GKP_NONPLAYEROBJECT_H
#define GKP_NONPLAYEROBJECT_H


#include "SimpleObject.h"

class NonPlayerObject : public SimpleObject{
public:
    NonPlayerObject(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao);
    void update() override;
protected:
    float lenght = 5;
};


#endif //GKP_NONPLAYEROBJECT_H
