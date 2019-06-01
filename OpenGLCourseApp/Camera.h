#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include <GLFW\glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);
	void posicionCameraKamikaze(glm::vec3 position, float angulo_kamikaze);
	void posicionCameraRuleta(glm::vec3 position);

	glm::vec3 getCameraPosition();
	void setCameraPosition(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	glm::vec3 worldUp_tmp;
	unsigned short mybool = 0;
	glm::vec3 saved_position_1;
	glm::vec3 saved_position_2;
	glm::vec3 saved_position_3;
	glm::vec3 saved_position_4;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat yaw_a[5];
	GLfloat pitch_a[5];
	unsigned short lastPosition = 0;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	void update();
};

