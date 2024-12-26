#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include "Shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);



int main() {

	int success;
	char infoLog[512];

	glfwInit();

	//openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl", NULL,NULL);

	if (window == NULL) { //if window not created
		std::cout << "Couldnt create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init GLAD" << std::endl;
		glfwTerminate();
		return -1;

	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*
			
	--------SHADERS-------
	
	*/

	Shader shader("Assets/vertex_core.glsl", "Assets/fragment_core.glsl");
	Shader shader2("Assets/vertex_core.glsl", "Assets/fragment_core2.glsl");
	

	//vertex array
	float vertices[] = {
		// Positions           // Colors
		-0.25f, -0.5f, 0.0f,   1.0f, 1.0f, 0.5f, // Vertex 0
		 0.15f,  0.0f, 0.0f,   0.5f, 1.0f, 0.75f, // Vertex 1
		 0.0f,   0.5f, 0.0f,   0.6f, 1.0f, 0.2f,  // Vertex 2
		 0.5f,  -0.4f, 0.0f,   1.0f, 0.2f, 1.0f   // Vertex 3
	};

	unsigned int indices[] = {
		0, 1, 2,  // First triangle
		3, 1, 2   // Second triangle
	};

	//VAO, VBO

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//bind VAO
	glBindVertexArray(VAO);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set atribute pointer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//matrix init
	
	
	glm::mat4 trans1 = glm::mat4(1.0f);
	glm::mat4 trans2 = glm::mat4(1.0f);


	trans1 = glm::rotate(trans1, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	trans2 = glm::scale(trans1, glm::vec3(1.5f));
	trans2 = glm::rotate(trans1, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	shader.activate();
	shader2.activate();



	shader.setMat4("transform", trans1);
	shader2.setMat4("transform", trans2);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Update transformations
		glm::mat4 trans1 = glm::rotate(glm::mat4(1.0f), glm::radians((float)glfwGetTime() * 10.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		// Draw first triangle
		shader.activate();
		shader.setMat4("transform", trans1);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		trans2 = glm::rotate(trans2, glm::radians((float)glfwGetTime() / -100.0f), glm::vec3(0.0f, 0.0f, 1.0f));

		// Draw second triangle
		shader2.activate();
		shader2.setMat4("transform", trans2);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)));

		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


