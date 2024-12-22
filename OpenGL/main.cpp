#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

std::string loadShaderSrc(const char* filename);


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

	//compile vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertShaderSrc = loadShaderSrc("Assets/vertex_core.glsl");
	const GLchar* vertShader = vertShaderSrc.c_str(); //getting is as string and converting it to GLchar*
	glShaderSource(vertexShader, 1, &vertShader, NULL); //shader source &vertShader
	glCompileShader(vertexShader);

	//catch error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //get shadervalue and gl compile status
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "error with vertex shader comp " << std::endl << infoLog << std::endl;
	}

	//compile fragment shader 
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShaderSrc = loadShaderSrc("Assets/fragment_core.glsl");
	const GLchar* fragShader = fragmentShaderSrc.c_str(); 
	glShaderSource(fragmentShader, 1, &fragShader, NULL);//shader source &fragShader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "error with fragment shader comp " << std::endl << infoLog << std::endl;
	}

	//create program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "error with shader program " << std::endl << infoLog << std::endl;

	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//vertex array
	float vertices[] = {

		-0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f

	}

	//VAO, VBO

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//bind VAO
	glBindVertexArray(VAO);

	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);





	while (!glfwWindowShouldClose(window)) {

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);


		//sends new buffer to window
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

std::string loadShaderSrc(const char* filename)
{
	std::ifstream file;
	std::stringstream buf;

	std::string ret = "";
	file.open(filename);

	if (file.is_open())
	{
		buf << file.rdbuf();
		ret = buf.str();
	}
	else
	{
		std::cout << "couldnt open " << filename << std::endl;
	}
	file.close();


	return ret;
}
