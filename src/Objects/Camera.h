#pragma once
//default values
#define DEFAULT_POSITION glm::vec3(-5.0f, 10.0f,0.0f)
#define DEFAULT_WORLD_UP  glm::vec3(0.0f, -1.0f, 0.0f)
#define DEFAULT_YAW 0.0f
#define DEFAULT_PITCH -45.0f
#define DEFAULT_VELO 100.0f
#define DEFAULT_SENSITIVTY 0.2f



class Camera
{
public:

	~Camera();
	Camera(glm::vec3 position = DEFAULT_POSITION, glm::vec3 up = DEFAULT_WORLD_UP, GLfloat yaw = DEFAULT_YAW, GLfloat pitch = DEFAULT_PITCH);
	glm::mat4 GetViewMatrix();

	void update();

	void moveForward(GLfloat value);

	void moveRight(GLfloat value);

	void moveUp(GLfloat value);

	void rotateCamera(GLfloat x,GLfloat y);
	glm::vec3 getPos();

	glm::vec3 getfront();
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	GLfloat yaw;
	GLfloat pitch;
	glm::vec3 worldUp;
	GLfloat mouseSensitivity;
	GLfloat velocity;

	void updateCameraVectors();
};

