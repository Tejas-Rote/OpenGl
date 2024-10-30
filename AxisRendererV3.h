#ifndef AXIS_RENDERER_V3_H
#define AXIS_RENDERER_V3_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"
#include "sphere.h" // Include sphere renderer for markers

class AxisRendererV3 {
public:
	GLuint VAO, VBO;  // Vertex Array Object and Vertex Buffer Object for the axis
	glm::vec3 axisColorX; // Color for X-axis
	glm::vec3 axisColorY; // Color for Y-axis
	glm::vec3 axisColorZ; // Color for Z-axis
	glm::vec3 markerColor; // Color for marker

	SphereRenderer sphereRenderer; // Sphere renderer for unit markers
	float markerRadius; // Radius of the marker spheres
	int numMarkers; // Number of markers per axis

	AxisRendererV3(glm::vec3 colorX = glm::vec3(1.0f, 0.0f, 0.0f),  // Red
		glm::vec3 colorY = glm::vec3(0.0f, 1.0f, 0.0f),  // Green
		glm::vec3 colorZ = glm::vec3(0.0f, 0.0f, 1.0f),  // Blue
		glm::vec3 markerColor = glm::vec3(1.0f, 1.0f, 1.0f),
		float markerRadius = 0.05f, // Default radius for markers
		int numMarkers = 10); // Default number of markers

	~AxisRendererV3();

	void render(Shader& shader, const glm::mat4& view, const glm::mat4& projection);
};

#endif // AXIS_RENDERER_V3_H
