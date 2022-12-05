#pragma once

#include "Sprite.h" 
#include "Vetores.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

using namespace std;

class SceneManager
{
public:
	static void resize(GLFWwindow* currentWindow, int width, int height);

	void initialize(GLuint width, GLuint height, string windowName, string texturePath);
	void run(Ponto3d backgroundColor);
	
private:
	GLFWwindow* window;
	Shader* shader;
	glm::vec4 ortho2D;
	glm::mat4 projection;
	vector <Sprite*> sprites;
	Sprite* selectedSprite;

	 void initializeGraphics(string windowName);
	 void checkEsc();
	 void checkFilters();
	 void render(Ponto3d backgroundColor);
	 void addShader(string vFilename, string fFilename);
	 void setupScene(string texturePath);
	 void setupCamera2D();
	 unsigned int loadTexture(string filename);
	 void printSprite(glm::vec3 position, glm::vec3 scale, unsigned int channel);
	 static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);
	 void moveStickers();
};