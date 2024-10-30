#ifndef SPHERE_RENDERER_H
#define SPHERE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include <vector>

class SphereRenderer {
public:
	GLuint VAO, VBO;
	int numSegments;   // Number of segments around the sphere (longitude)
	int numRings;      // Number of rings along the sphere (latitude)
	float radius;      // Radius of the sphere
	int numIndices;
	glm::vec3 color;   // Custom color for the sphere
	SphereRenderer(float radius, int numSegments, int numRings, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
	~SphereRenderer();

	// Render the sphere
	void render(Shader& shader, const glm::mat4& model) const;
};

#endif // SPHERE_RENDERER_H
