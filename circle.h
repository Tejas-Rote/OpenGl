#ifndef CIRCLE_RENDERER_H
#define CIRCLE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"

class CircleRenderer {
public:
	GLuint VAO, VBO;
	float radius;
	int numSegments;  // Add numSegments as a member variable
	glm::vec3 color;  // Color of the circle (using glm::vec3 for RGB)

	CircleRenderer(float radius, int numSegments, const glm::vec3& color);
	~CircleRenderer();

	// Render the circle
	void render(Shader& shader, const glm::mat4& transform) const;
};

#endif // CIRCLE_RENDERER_H
