#include "shap.h"
#include "logger.h"  // Include your updated Logger
#include <iostream>

Shape::Shape() : VAO(0), VBO(0), shaderProgram(0) {}

Shape::~Shape() {
	if (VAO) glDeleteVertexArrays(1, &VAO);
	if (VBO) glDeleteBuffers(1, &VBO);
	if (shaderProgram) glDeleteProgram(shaderProgram);
}

unsigned int Shape::compileShader(const char* source, GLenum type) {
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);

		// Use the updated Logger to log the error
		Logger::Log("Shader Compilation Failed: " + std::string(infoLog), LogLevel::ERROR);
	}
	else {
		Logger::Log("Shader compiled successfully", LogLevel::INFO);
	}

	return shader;
}

unsigned int Shape::createShaderProgram(const char* vertexSource, const char* fragmentSource) {
	unsigned int vertexShader = compileShader(vertexSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fragmentSource, GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);

		// Use the updated Logger to log the error
		Logger::Log("Shader Linking Failed: " + std::string(infoLog), LogLevel::ERROR);
	}
	else {
		Logger::Log("Shader program linked successfully", LogLevel::INFO);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}
