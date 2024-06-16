// Ensure precompiled header is included first
#include "stdafx.h"
#include <GL\glew.h>
#include <GLFW/glfw3.h> // Correctly include the GLFW header

int main()
{
// Initialize the library
if (!glfwInit()) {
return -1; // Exit if initialization fails
}

// Set GLFW window creation hints
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// Uncomment if on MacOS
// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

// Create a windowed mode window and its OpenGL context
GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
if (!window) {
	glfwTerminate();
	return -1;
}

// Make the window's context current
glfwMakeContextCurrent(window);

// Main loop
while (!glfwWindowShouldClose(window)) {
	// Render here

	// Swap front and back buffers
	glfwSwapBuffers(window);

	// Poll for and process events
	glfwPollEvents();
}

glfwTerminate(); // Clean up and close the library
return 0;

}
