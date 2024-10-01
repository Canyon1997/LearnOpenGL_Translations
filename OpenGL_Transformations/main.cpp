// Core Libraries
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

// GLM Libraries
#include "ExternalLibraries/glm/glm.hpp"
#include "ExternalLibraries/glm/gtc/matrix_transform.hpp"
#include "ExternalLibraries/glm/gtc/type_ptr.hpp"

// Personal/External Libraries
#include "OpenGLOperations.h"
#include "Shader.h"
#include "stb_image.h"

int main()
{
	GLFWwindow* window = InitializeOpenGL("Translations");

	Shader woodenShader("Shaders//WoodenVertexShader.glsl", "Shaders//WoodenFragmentShader.glsl");

	float vertices[]{
		0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // bottom right
		0.5f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f,   1.0f, 1.0f,// top right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,// bottom left
		-0.5f, 0.5f, 0.0f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f// top left
	};

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 1
	};

	unsigned int VBO, VAO, EBO, TBO1, TBO2;

	// Vertex Buffer Object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Element Buffer Object
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Texture Buffer Objects
	glGenTextures(1, &TBO1);
	glBindTexture(GL_TEXTURE_2D, TBO1);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, woodNRChannel;
	unsigned char* woodTextureData = stbi_load("Textures//woodencontainer.jpg", &width, &height, &woodNRChannel, 0);
	if (woodTextureData != nullptr)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, woodTextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}
	stbi_image_free(woodTextureData);

	glGenTextures(1, &TBO2);
	glBindTexture(GL_TEXTURE_2D, TBO2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width2, height2, NrChannel2;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* faceTextureData = stbi_load("Textures//awesomeface.png", &width2, &height2, &NrChannel2, 0);
	if (faceTextureData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, faceTextureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		return -1;
	}
	stbi_image_free(faceTextureData);

	woodenShader.Use();
	woodenShader.setInt("firstTexture", 0);
	woodenShader.setInt("secondTexture", 1);
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TBO1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TBO2);
		woodenShader.Use();

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, indices);
		
		//Swap color buffer and shows output to screen
		glfwSwapBuffers(window);

		//check if any events triggered
		glfwPollEvents();
	}


	// Clean-up
	glfwTerminate();

	return 0;
}