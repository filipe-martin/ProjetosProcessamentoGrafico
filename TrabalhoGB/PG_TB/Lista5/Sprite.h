#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sprite
{
public:
	Sprite();
	~Sprite() {}

	void initialize(); 
	void setShader(Shader* shader);
	glm::vec3 position, scale;
	float angle;
	int channel;
	unsigned int textureID;

	void setRotation(float angle, glm::vec3 axis, bool reset = true);
	void setTranslation(glm::vec3 displacements, bool reset = true);
	void setScale(glm::vec3 scaleFactors);

	void draw(int channel);
	void update();

protected:
	GLuint VAO;
	glm::mat4 transform;
	Shader* shader;
	int nAnims, nFrames, iAnim, iFrame;
};