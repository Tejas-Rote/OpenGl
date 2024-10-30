#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // Include glad for OpenGL function pointers
#include <glm/glm.hpp> // Include GLM for math operations
#include <string>

class Shader {
public:
	// Shader Program ID
	GLuint ID;

	// Constructor that builds the shader from the given vertex and fragment shader paths
	Shader(const char* vertexPath, const char* fragmentPath);

	// Use the shader program
	void use() const;

	// Uniform utility functions
	void setBool(const std::string& name, bool value) const; // Set boolean uniform
	void setInt(const std::string& name, int value) const;   // Set integer uniform
	void setFloat(const std::string& name, float value) const; // Set float uniform
	void setVec3(const std::string& name, const glm::vec3& value) const; // Set vec3 uniform
	void setMat4(const std::string& name, const glm::mat4& mat) const; // Set mat4 uniform

private:
	// Utility function to check for shader compilation/linking errors
	void checkCompileErrors(GLuint shader, const std::string& type);
};

#endif // SHADER_H
