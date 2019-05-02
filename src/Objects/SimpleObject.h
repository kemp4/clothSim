#pragma once
#include "AbstractGameObject.h"
#include "src/ResoureManagment/Shader.h"
#include "src/ResoureManagment/Texture.h"
#include "src/ResoureManagment/VaoObject.h"
#include "list"

class SimpleObject :
	public AbstractGameObject
{
public:
	SimpleObject();
	SimpleObject(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao);
	SimpleObject(glm::mat4 transform, Shader * shader, Texture texture, VaoObject * vao);
	SimpleObject(glm::vec3 position);
	SimpleObject(Texture texture, glm::mat4 modelMatrix, VaoObject* VAO);



	~SimpleObject();

    void update() override;
    void draw() override;
	virtual void setShader(Shader * shader);
	void setTexture(Texture texture);
	void setVao(VaoObject * vao);
    void setPosition(glm::vec3 position) override;
    glm::vec3 getPosition() override;
    void setVisible(bool visible) override;
    bool isVisible() override;
	void move(glm::vec3 value);
	std::list<AbstractGameObject*> getChildren() override;

	void addChildren(AbstractGameObject *child);

protected:

	std::list<AbstractGameObject*> children;
	glm::mat4 modelMatrix;
	Shader * shader;
	VaoObject * vao;
	Texture texture;

	virtual void setVAO(VaoObject* VAO);
	virtual void setModelMatrix(glm::mat4 modelMatrix);

};

