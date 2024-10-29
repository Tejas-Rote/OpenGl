#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
	GLuint ID;

	// Constructor that builds the shader program from two source paths
	Shader(const char* vertexPath, const char* fragmentPath);

	// Activate the shader
	void use() const;

	// Utility function to set a 3D vector (vec3) in the shader
	void setVec3(const std::string& name, const glm::vec3& vec) const;

	// Utility function to set a 4x4 matrix in the shader
	void setMat4(const std::string& name, const glm::mat4& mat) const;

private:
	// Check for shader compile/link errors
	void checkCompileErrors(GLuint shader, const std::string& type);
};

#endif
