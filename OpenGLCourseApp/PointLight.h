#pragma once
#include "Light.h"
#include <GLFW\glfw3.h>
class PointLight :
	public Light
{
public:
	PointLight();
	PointLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat con, GLfloat lin, GLfloat exp);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientcolorLocation,
		GLfloat diffuseIntensityLocation, GLfloat positionLocation,
		GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);


	void TurnOnLight();
	void TurnOffLight();
	void keyControl(bool* keys);
	~PointLight();

protected:
	glm::vec3 position;

	GLfloat constant, linear, exponent;
};

