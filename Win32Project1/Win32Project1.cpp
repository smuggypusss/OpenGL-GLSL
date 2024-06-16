#include "stdafx.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void display() {
	glClearColor(1.0, 0.0, 0.0, 1.0); // Set clear color to red
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
}

int main() {
	// Initialize GLFW
	if (!glfwInit()) {
		//std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Set OpenGL version to 4.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(980, 720, "Red Screen", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		//std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Enable V-Sync
	glfwSwapInterval(1);

	// Main loop
	while (!glfwWindowShouldClose(window)) {
		display(); // Render the red screen

				   // Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}

	// Cleanup
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
