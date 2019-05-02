#pragma once
#include <glm/glm.hpp>
#include <list>

 class AbstractGameObject
{
public:
	AbstractGameObject();
	virtual ~AbstractGameObject();
	virtual void setPosition(glm::vec3 position)=0;
	virtual glm::vec3 getPosition() = 0;
	virtual void update()=0;
	virtual void draw()=0;
	virtual void setVisible(bool visible)=0;
	virtual bool isVisible()=0;
	virtual std::list<AbstractGameObject*> getChildren()=0;
	virtual void move(glm::vec3)=0;
protected:
	bool visible;

};

