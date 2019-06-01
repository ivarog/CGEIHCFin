#include "Camera.h"
#include <stdio.h>

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	worldUp_tmp = worldUp;
	for (int i = 0; i < 5; i++)
	{
		yaw_a[i] = startYaw;
		pitch_a[i] = startPitch;
	}

	yaw_a[0] = 40.5;
	pitch_a[0] = 23.50;

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	saved_position_1 = glm::vec3(-15.0f, 1.0f, -15.0f);
	saved_position_2 = glm::vec3(30.0f, 50.0f, 13.0f);
	saved_position_3 = glm::vec3(13.0f, 8.0f, 0.0f);
	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W] && mybool != 1 && mybool != 2 && mybool != 3 && mybool != 4)
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_S] && mybool != 1 && mybool != 2 && mybool != 3 && mybool != 4)
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_A] && mybool != 2 && mybool != 3 && mybool != 4)
	{
		position -= right * velocity;
	}

	if (keys[GLFW_KEY_D] && mybool != 2 && mybool != 3 && mybool != 4)
	{
		position += right * velocity;
	}

	if (keys[GLFW_KEY_1])
	{
		mybool = 0;
		position = saved_position_1;
	}

	if (keys[GLFW_KEY_2])
	{
		mybool = 1;
		position = saved_position_2;
	}

	
	if (keys[GLFW_KEY_3])
	{
		mybool = 2;
		position = saved_position_3;
	}

	if (keys[GLFW_KEY_4])
	{
		mybool = 3;
	}

	if (keys[GLFW_KEY_5])
	{
		mybool = 4;
	}

	switch(mybool)
	{
		case 0:
			saved_position_1 = position;
			break;
		case 1:
			saved_position_2 = position;
			break;
		case 2:
			saved_position_3 = position;
			break;
	}

	if(mybool != 3){
		worldUp = worldUp_tmp;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	yaw = yaw_a[mybool];
	pitch = pitch_a[mybool];

	xChange *= turnSpeed;
	yChange *= turnSpeed;

	if (lastPosition != mybool)
	{
		xChange = 0.0f;
		yChange = 0.0f;
		lastPosition = mybool;
	}

	yaw += xChange;
	pitch += yChange;

	yaw_a[mybool] = yaw;
	pitch_a[mybool] = pitch;

	if (mybool == 1)
	{
		pitch = -89.0f;
		yaw = -89.50f;
	}else {
		if (pitch > 89.0f)
		{
			pitch = 89.0f;
		}

		if (pitch < -89.0f)
		{
			pitch = -89.0f;
		}
	}
	update();
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

void Camera::setCameraPosition(GLfloat x, GLfloat y, GLfloat z)
{
	position = glm::vec3(x, y, z);
}


glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::posicionCameraKamikaze(glm::vec3 position, float angulo_kamikaze)
{
	// printf("angulo %f\n", angulo_kamikaze);
	if (mybool == 3) {
		Camera::position = position;
		if ((angulo_kamikaze > 90 && angulo_kamikaze < 270) || 
		(angulo_kamikaze > - 270 && angulo_kamikaze < - 90))
		{
			worldUp = glm::vec3(0.0f, -1.0f, 0.0f);
		}else {
			worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		}
	}
}

void Camera::posicionCameraRuleta(glm::vec3 position)
{
	if (mybool == 4) {
		Camera::position = position;
	}
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}


Camera::~Camera()
{
}
