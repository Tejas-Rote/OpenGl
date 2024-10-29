#ifndef AXIS_RENDERER_H
#define AXIS_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "Shader.h"

class AxisRenderer {
public:
	GLuint VAO, VBO;

	AxisRenderer();
	~AxisRenderer();

	// Render the axes
	void render(Shader& shader, const glm::mat4& transform) const;
};

#endif
