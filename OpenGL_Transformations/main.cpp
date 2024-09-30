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
		0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f, // bottom right
		0.5f, 0.5f, 0.0f,     0.0f, 1.0f, 0.0f, // top right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // bottom left
		-0.5f, 0.5f, 0.0f,    1.0f, 1.0f, 0.0f, // top left
	};

	unsigned int indices[]{
		0, 1, 2,
		2, 3, 1
	};

	unsigned int VBO, VAO, EBO;

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// EBO
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	woodenShader.Use();
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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