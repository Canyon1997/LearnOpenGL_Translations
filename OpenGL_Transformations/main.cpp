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