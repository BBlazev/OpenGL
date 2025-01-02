#pragma once
#include <glad/glad.h>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>



class Shader
{
public:

	unsigned int id;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void activate();

	std::string loadShaderSrc(const char* filepath);
	GLuint compileShader(const char* filepath, GLenum type);

	void setMat4(const std::string& name, glm::mat4 val);
	void setInt(const std::string& name, int value);
};

 