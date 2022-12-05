#include "SceneManager.h"

static bool resized;
static GLuint width, height, baseWidht, baseHeight;
static float mouseXPosition;
static float mouseYPosition;
static bool enterIsPressing = false;
static bool filtersArePressing[16] = { false };
static bool saveIsPressing = false;

void SceneManager::initialize(GLuint w, GLuint h, string windowName, string texturePath)
{
	baseWidht = width = w;
	baseHeight = height = h;

	initializeGraphics(windowName);
	setupScene(texturePath);
}

void SceneManager::initializeGraphics(string windowName)
{
	glfwInit();

	window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, resize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	addShader("../shaders/transformations.vs", "../shaders/transformations.fs");

	resized = true;
}

void SceneManager::addShader(string vFilename, string fFilename)
{
	shader = new Shader(vFilename.c_str(), fFilename.c_str());
}

void SceneManager::resize(GLFWwindow* currentWindow, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	glViewport(0, 0, width, height);
}


void SceneManager::checkEsc()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void SceneManager::checkFilters()
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		if (filtersArePressing[0])
		{
			return;
		}
		filtersArePressing[0] = true;
		sprites[0]->channel ^= 1;
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		if (filtersArePressing[1])
		{
			return;
		}
		filtersArePressing[1] = true;
		sprites[0]->channel ^= 2;
	}
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		if (filtersArePressing[2])
		{
			return;
		}
		filtersArePressing[2] = true;
		sprites[0]->channel ^= 4;
	}
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		if (filtersArePressing[3])
		{
			return;
		}
		filtersArePressing[3] = true;
		sprites[0]->channel ^= 8;
	}
	else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		if (filtersArePressing[4])
		{
			return;
		}
		filtersArePressing[4] = true;
		sprites[0]->channel ^= 16;
	}
	else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		if (filtersArePressing[5])
		{
			return;
		}
		filtersArePressing[5] = true;
		sprites[0]->channel ^= 32;
	}
	else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		if (filtersArePressing[6])
		{
			return;
		}
		filtersArePressing[6] = true;
		sprites[0]->channel ^= 64;
	}
	else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
	{
		if (filtersArePressing[7])
		{
			return;
		}
		filtersArePressing[7] = true;
		sprites[0]->channel ^= 128;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (filtersArePressing[8])
		{
			return;
		}
		filtersArePressing[8] = true;
		sprites[0]->channel ^= 256;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		if (filtersArePressing[9])
		{
			return;
		}
		filtersArePressing[9] = true;
		sprites[0]->channel ^= 512;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (filtersArePressing[10])
		{
			return;
		}
		filtersArePressing[10] = true;
		sprites[0]->channel ^= 1024;
	}
	else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		if (filtersArePressing[11])
		{
			return;
		}
		filtersArePressing[11] = true;
		sprites[0]->channel ^= 2048;
	}
	else if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
	{
		if (filtersArePressing[12])
		{
			return;
		}
		filtersArePressing[12] = true;
		sprites[0]->channel ^= 4096;
	}
	else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
	{
		if (filtersArePressing[13])
		{
			return;
		}
		filtersArePressing[13] = true;
		sprites[0]->channel ^= (2 << 12);
	}
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		if (filtersArePressing[14])
		{
			return;
		}
		filtersArePressing[14] = true;
		sprites[0]->channel ^= (2 << 13);
	}
	else if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
	{
		if (filtersArePressing[15])
		{
			return;
		}
		filtersArePressing[15] = true;
		sprites[0]->channel ^= (2 << 14);
	}
	else
	{
		for (int i = 0; i < 16; i++)
		{
			filtersArePressing[i] = false;
		}
	}
}

void SceneManager::render(Ponto3d backgroundColor)
{
	glClearColor(backgroundColor.x, backgroundColor.y,backgroundColor.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (resized)
	{
		setupCamera2D();
		resized = false;
	}

	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->update();
		sprites[i]->draw(sprites[i]->channel);
	}
}

void SceneManager::run(Ponto3d backgroundColor)
{
	while (!glfwWindowShouldClose(window))
	{
        glfwPollEvents();

		checkEsc();
		checkFilters();
		glfwSetCursorPosCallback(window, cursorPositionCallback);
		moveStickers();

		render(backgroundColor);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
}

void SceneManager::setupScene(string texturePath)
{
	//Main sprite
	printSprite(glm::vec3(350,300, 0.0), glm::vec3(700, 600, 1.0f),5);
	sprites[0]->textureID = loadTexture(texturePath);
	sprites[0]->channel = 0;

	//Stickers
	printSprite(glm::vec3(750, 60, 0.0), glm::vec3(100, 100, 1.0f), 0);
	printSprite(glm::vec3(750, 180, 0.0), glm::vec3(100, 100, 1.0f), 0);
	printSprite(glm::vec3(750, 300, 0.0), glm::vec3(100, 100, 1.0f), 0);
	printSprite(glm::vec3(750, 420, 0.0), glm::vec3(100, 100, 1.0f), 0);
	printSprite(glm::vec3(750, 540, 0.0), glm::vec3(100, 100, 1.0f), 0);

	sprites[1]->textureID = loadTexture("../textures/The_Game_Awards.png");
	sprites[2]->textureID = loadTexture("../textures/kojima.png");
	sprites[3]->textureID = loadTexture("../textures/valve3.png");
	sprites[4]->textureID = loadTexture("../textures/Sony.png");
	sprites[5]->textureID = loadTexture("../textures/xbox.png");

	ortho2D[0] = 0.0f;
	ortho2D[1] = 800.0f;
	ortho2D[2] = 0.0f;
	ortho2D[3] = 600.0f;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SceneManager::printSprite(glm::vec3 position, glm::vec3 scale, unsigned int channel)
{
	Sprite* sprite = new Sprite;
	sprite->position = position;
	sprite->scale = scale;
	sprite->setShader(shader);
	sprite->channel = channel;
	sprites.push_back(sprite);
}

void SceneManager::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	mouseXPosition = xPos * ((float)baseWidht / width) * 800./baseWidht;
	mouseYPosition = 600 - (yPos * ((float)baseHeight / height) * 600./baseHeight);
}

void SceneManager::moveStickers()
{
	for (int i = 1; i < sprites.size(); i++)
	{
		if ((mouseXPosition >= (sprites[i]->position.x - sprites[i]->scale.x / 2)) &&
			(mouseXPosition <= (sprites[i]->position.x + sprites[i]->scale.x / 2)) &&
			(mouseYPosition >= (sprites[i]->position.y - sprites[i]->scale.y / 2)) &&
			(mouseYPosition <= (sprites[i]->position.y + sprites[i]->scale.y / 2)))
		{
			if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
			{
				if (enterIsPressing)
				{
					return;
				}
				enterIsPressing = true;
				if (selectedSprite == NULL)
				{
					selectedSprite = sprites[i];
				}
				else
				{
					selectedSprite = NULL;
				}
			}
			else
			{
				enterIsPressing = false;
			}
		}
	}

	if (selectedSprite != NULL)
	{
		selectedSprite->position.x = mouseXPosition;
		selectedSprite->position.y = mouseYPosition;
	}
}

void SceneManager::setupCamera2D()
{
	float zNear = -1.0, zFar = 1.0;

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);

	GLint projLoc = glGetUniformLocation(shader->ID, "projection");

	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

unsigned int SceneManager::loadTexture(string filename)
{
	unsigned int texture1;

	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;

	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	
	return texture1;
}