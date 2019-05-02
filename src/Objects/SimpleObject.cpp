#include "src/baseHeader.h"
#include "SimpleObject.h"

//using namespace tinyxml2;

SimpleObject::SimpleObject()
{
	//modelMatrix;// = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f))
}

SimpleObject::SimpleObject(glm::vec3 position, Shader * shader, Texture texture, VaoObject * vao)
{
	this->setPosition(position);
	this->setShader(shader);
	this->setTexture(texture);
	this->setVao(vao);

}

SimpleObject::SimpleObject(glm::mat4 transform, Shader * shader, Texture texture, VaoObject * vao)
{
	setModelMatrix(transform);
	this->setShader(shader);
	this->setTexture(texture);
	this->setVao(vao);
}

SimpleObject::SimpleObject(glm::vec3 position)
{
	SimpleObject();
}

SimpleObject::SimpleObject(Texture texture, glm::mat4 modelMatrix, VaoObject * VAO)
{
	setTexture(texture);

	setModelMatrix(modelMatrix);
	setVAO(VAO);
}


SimpleObject::~SimpleObject()
{
}

void SimpleObject::update()
{

}

void SimpleObject::draw()
{
	if (visible) {
		texture.bind();
		glBindVertexArray(vao->getID());
		GLint modelLoc = glGetUniformLocation(shader->getID(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
		glDrawArrays(GL_TRIANGLES, 0, vao->getTrianglesNumber());
		glBindVertexArray(0);
	}
}

void SimpleObject::setShader(Shader * shader)
{
	this->shader = shader;
}

void SimpleObject::setTexture(Texture texture)
{
	this->texture = texture;
}

void SimpleObject::setVao(VaoObject * vao)
{
	this->vao = vao;
}

void SimpleObject::setPosition(glm::vec3 position)
{
	modelMatrix=glm::translate(glm::mat4(),position);
}

glm::vec3 SimpleObject::getPosition()
{
	return glm::vec3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
}

void SimpleObject::setVisible(bool visible)
{
	this->visible = visible;
}

bool SimpleObject::isVisible()
{
	return visible;
}


void SimpleObject::setVAO(VaoObject * VAO)
{
	this->vao = VAO;
}

void SimpleObject::setModelMatrix(glm::mat4 modelMatrix)
{
	this->modelMatrix = modelMatrix;
}

void SimpleObject::move(glm::vec3 value) {
	modelMatrix = glm::translate(modelMatrix, value);
	for (auto &child : getChildren())
	{
		child->move(value);
	}

}

std::list<AbstractGameObject *> SimpleObject::getChildren() {
	return children;
}

void SimpleObject::addChildren(AbstractGameObject *child) {
    children.push_front(child);
}

