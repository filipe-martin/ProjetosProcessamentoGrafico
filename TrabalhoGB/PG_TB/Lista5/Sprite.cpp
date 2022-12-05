#include "Sprite.h"

Sprite::Sprite()
{
	initialize();
}

void Sprite::initialize()
{
	float vertices[] = {
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0,
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	unsigned int VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Sprite:: setShader(Shader* shader)
{
	this->shader = shader;
	shader->Use();
}

void Sprite::setRotation(float angle, glm::vec3 axis, bool reset)
{
	if (reset)
	{
		transform = glm::mat4(1);
	}
	transform = glm::rotate(transform, angle, axis);
}

void Sprite::setTranslation(glm::vec3 displacements, bool reset)
{
	if (reset)
	{
		transform = glm::mat4(1);
	}
	transform = glm::translate(transform, displacements);
}

void Sprite::setScale(glm::vec3 scaleFactors)
{
	transform = glm::scale(transform, scaleFactors);
	scale = scaleFactors;
}

void Sprite::draw(int channel)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glUniform1i(glGetUniformLocation(shader->ID, "ourTexture1"), 0);

	glUniform1i(glGetUniformLocation(shader->ID, "channel"), channel);
	glUniform3f(glGetUniformLocation(shader->ID, "modifier"), 0.8f, 0.3f, 0.3f);
	glUniform3f(glGetUniformLocation(shader->ID, "resolution"), 1800, 1000, 0);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Sprite::update()
{
	setTranslation(position);
	setRotation(angle, glm::vec3(0.0f, 0.0f, 1.0f), false);
	setScale(scale);

	GLint transformLoc = glGetUniformLocation(shader->ID, "model");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}