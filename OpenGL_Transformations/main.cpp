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

// TODO: continue on "Texture Units" section of Textures lesson in OpenGL

int main()
{
	GLFWwindow* window = InitializeOpenGL("Translations");

	Shader woodenShader("Shaders//WoodenVertexShader.glsl", "Shaders//WoodenFragmentShader.glsl");

	float vertices[]{
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
		0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f // top middle
	};

	/*
	// Translates a vector by "trans" identity value
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl;

	// Scale and rotate object
	glm::mat4 trans2 = glm::mat4(1.0f);
	trans2 = glm::rotate(trans2, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans2 = glm::scale(trans2, glm::vec3(0.5, 0.5, 0.5));
	*/

	unsigned int VBO, VAO;

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	
	
	
	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		//set background color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//Swap color buffer and shows output to screen
		glfwSwapBuffers(window);

		//check if any events triggered
		glfwPollEvents();
	}


	// Clean-up
	glfwTerminate();

	return 0;
}