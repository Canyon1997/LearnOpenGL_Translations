#ifndef OPENGLOPERATIONS_H
#define OPENGLOPERATIONS_H


#include <fstream>
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <sstream>
#include <string>

/// <summary>
/// Initializes external libraries and a window to be used for rendering
/// </summary>
/// <param name="windowName">The name the window will be called</param>
/// <returns>Pointer to the window upon successful initialization of all libraries</returns>
GLFWwindow* InitializeOpenGL(const std::string& windowName);

/// <summary>
/// Callback function that gets called each time the window is resized
/// </summary>
/// <param name="window">The window that will be resized</param>
/// <param name="width">Width of the window</param>
/// <param name="height">Height of the window</param>
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);

/// <summary>
/// Performs any operations from inputs by the user when something specific is pressed
/// </summary>
/// <param name="window">The window to perform the input on</param>
void ProcessInput(GLFWwindow* window);

#endif // !OPENGLOPERATIONS_H