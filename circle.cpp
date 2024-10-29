//#include "circle.h"
//#include <vector>
//#include <cmath> // For M_PI
//
//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif
//
//CircleRenderer::CircleRenderer(float radius, int numSegments) {
//	std::vector<GLfloat> vertices;
//
//	// Generate circle vertices
//	vertices.push_back(0.0f); // Center of the circle (x)
//	vertices.push_back(0.0f); // Center of the circle (y)
//	vertices.push_back(0.0f); // Center of the circle (z)
//	vertices.push_back(1.0f); // Color R (red)
//	vertices.push_back(0.0f); // Color G (green)
//	vertices.push_back(0.0f); // Color B (blue)
//
//	for (int i = 0; i <= numSegments; ++i) {
//		float angle = 2.0f * M_PI * i / numSegments; // Calculate the angle
//		float x = radius * cos(angle); // Calculate x coordinate
//		float y = radius * sin(angle); // Calculate y coordinate
//
//		// Add vertex position
//		vertices.push_back(x);
//		vertices.push_back(y);
//		vertices.push_back(0.0f); // Z coordinate
//		vertices.push_back(1.0f); // Color R (red)
//		vertices.push_back(0.0f); // Color G (green)
//		vertices.push_back(0.0f); // Color B (blue)
//	}
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
//
//	// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
//	glEnableVertexAttribArray(0);
//	// Color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//}
//
//CircleRenderer::~CircleRenderer() {
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//}
//
//void CircleRenderer::render(Shader& shader, const glm::mat4& transform) const {
//	shader.use();
//	shader.setMat4("transform", transform);
//
//	glBindVertexArray(VAO);
//
//	// Draw the circle using a triangle fan
//	glDrawArrays(GL_TRIANGLE_FAN, 0, 100); // Assuming 100 segments for smoothness
//}




#include "circle.h"
#include <vector>
#include <cmath> // For M_PI

// Define M_PI if it is not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

CircleRenderer::CircleRenderer(float radius, int segments, const glm::vec3& color) : numSegments(segments), radius(radius), color(color) {  // Initialize numSegments
	std::vector<GLfloat> vertices;

	// Center of the circle (for the triangle fan)
	vertices.push_back(0.0f); // Center x
	vertices.push_back(0.0f); // Center y
	vertices.push_back(0.0f); // Center z
	//vertices.push_back(1.0f); // Color R
	//vertices.push_back(0.0f); // Color G
	//vertices.push_back(0.0f); // Color B
	vertices.push_back(color.r); // Color R
	vertices.push_back(color.g); // Color G
	vertices.push_back(color.b); // Color B


	for (int i = 0; i <= numSegments; ++i) {
		float angle = 2.0f * M_PI * i / numSegments; // Calculate the angle
		float x = radius * cos(angle); // Calculate x coordinate
		float y = radius * sin(angle); // Calculate y coordinate

		// Add vertex position for the perimeter
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(0.0f); // Z coordinate
		//vertices.push_back(1.0f); // Color R
		//vertices.push_back(0.0f); // Color G
		//vertices.push_back(0.0f); // Color B
		vertices.push_back(color.r); // Color R
		vertices.push_back(color.g); // Color G
		vertices.push_back(color.b); // Color B

	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
}

CircleRenderer::~CircleRenderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void CircleRenderer::render(Shader& shader, const glm::mat4& transform) const {
	shader.use();
	shader.setMat4("transform", transform);

	glBindVertexArray(VAO);

	// Draw the circle using a triangle fan
	glDrawArrays(GL_TRIANGLE_FAN, 0, numSegments + 2); // +2 to account for center and all perimeter vertices
}
