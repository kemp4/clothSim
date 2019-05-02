#include "src/baseHeader.h"
#include "Camera.h"




Camera::~Camera()
{
}

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
{
	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	this->updateCameraVectors();
	this->velocity = DEFAULT_VELO;
	this->mouseSensitivity = DEFAULT_SENSITIVTY;
}

glm::mat4 Camera::GetViewMatrix()
{

	return glm::lookAt(position,position  +this->front,
		-this->up);
}

glm::vec3 Camera::getPos() {
	return this->position;
}

glm::vec3 Camera::getfront()
{
	return front;
}

void Camera::update()
{
	updateCameraVectors();
}

void Camera::moveForward(GLfloat value)
{
		position += front * velocity*value;
}

void Camera::moveRight(GLfloat value)
{
		position += right * velocity*value;
}
void Camera::moveUp(GLfloat value)
{
		position += up * velocity*value;
}

void Camera::rotateCamera(GLfloat x, GLfloat y)
{
	yaw -= x*mouseSensitivity;
	pitch += y*mouseSensitivity;
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	this->up = glm::normalize(glm::cross(this->right, this->front));
}
