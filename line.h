#ifndef LINERENDERER_H
#define LINERENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"

class LineRenderer {
public:
	GLuint VAO, VBO;
	LineRenderer(const glm::vec3& start, const glm::vec3& end, const glm::vec3& startColor, const glm::vec3& endColor);
	~LineRenderer();

	// Renders the line using a given shader and transformation matrix
	void render(Shader& shader, const glm::mat4& transform) const;

private:
	GLfloat vertices[12];  // Stores vertex positions and colors
};

#endif // LINERENDERER_H
