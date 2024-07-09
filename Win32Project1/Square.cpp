#include "stdafx.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processinput(GLFWwindow* window);

//settings
const unsigned int win_width = 800;
const unsigned int win_height = 600;
const char* vertexShaderSource = "#version 330 core\n"
	"layout(location=0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	" gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0);\n"
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
	"}\n\0";

int main() {
	//initialize glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);//For forward compatibility check
#endif // DEBUG
	//glfw
	GLFWwindow* window = glfwCreateWindow(win_width, win_height,"Test",NULL,NULL);
	if (window==NULL) {
		std::cout << "Failed to create a GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//load glew funtion pointer to avoid using GLAD
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize Glew" << std::endl;
		return -1;
	}
	//build and compile shaders
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check form compilation errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\\n" << infoLog << std::endl;
	}
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//check for compilation error
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\\n" << infoLog << std::endl;
	}
	//link shader
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//check for errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//get vertices
	float vertices[] = {
		-0.5f, 0.5f, 0.0f, // top left point
		0.5f, 0.5f, 0.0f, // top right point
		0.5f, -0.5f, 0.0f, // bottom right point
		0.5f, -0.5f, 0.0f, // bottom right point
		-0.5f, -0.5f, 0.0f, // bottom left point
		- 0.5f, 0.5f, 0.0f, // top left point
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),(void*)0);//in one ro how many numbers represent a vertice,sizeof(float)*3 represents after how many places another vertice will be present.
	glEnableVertexAttribArray(0);//?
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	while (!glfwWindowShouldClose(window)) {
		processinput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	//De-Allocate resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwTerminate();
	return 0;


}
void processinput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

}
