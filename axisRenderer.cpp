#include "AxisRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

AxisRenderer::AxisRenderer() {
	GLfloat vertices[] = {
		// X-axis (red)
		-0.8f, 0.0f, 0.0f,  0.75f, 0.75f,0.75f,  // Start point (x, y, z) and color (r, g, b)
		 0.8f, 0.0f, 0.0f,  0.75f, 0.75f,0.75f,  // End point (x, y, z) and color (r, g, b)

		 // Y-axis (green)
		 0.0f, -0.8f, 0.0f,  0.75f, 0.75f,0.75f,  // Start point (x, y, z) and color (r, g, b)
		 0.0f,  0.8f, 0.0f,  0.75f, 0.75f,0.75f,  // End point (x, y, z) and color (r, g, b)

		 // Z-axis (blue)
		 0.0f, 0.0f, -0.8f,  0.75f, 0.75f,0.75f,  // Start point (x, y, z) and color (r, g, b)
		 0.0f, 0.0f,  0.8f,  0.75f, 0.75f,0.75f   // End point (x, y, z) and color (r, g, b)
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);  // position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));  // color attribute
	glEnableVertexAttribArray(1);
}

AxisRenderer::~AxisRenderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void AxisRenderer::render(Shader& shader, const glm::mat4& transform) const {
	shader.use();
	shader.setMat4("transform", transform);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6);  // Draw the 3 axes
}


// AxisRenderer.cpp
//#include "axisRenderer.h"
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <vector>
//
//AxisRenderer::AxisRenderer() {
//	const int segments = 10; // Number of segments per axis
//	const float length = 2.0f; // Length of each axis
//	const float segmentLength = length / segments; // Length of each segment
//
//	std::vector<GLfloat> vertices;
//
//	// Generate vertices for X-axis (Red)
//	for (int i = 0; i <= segments; ++i) {
//		float x = -length / 2 + (i * segmentLength);
//		vertices.push_back(x); // X
//		vertices.push_back(0.0f); // Y
//		vertices.push_back(0.0f); // Z
//		vertices.push_back(1.0f); // Red
//		vertices.push_back(0.0f); // Green
//		vertices.push_back(0.0f); // Blue
//
//		// Add marker for the segment
//		if (i < segments) {
//			vertices.push_back(x + segmentLength / 2); // X for segment marker
//			vertices.push_back(0.0f); // Y
//			vertices.push_back(0.0f); // Z
//			vertices.push_back(1.0f); // Red
//			vertices.push_back(0.0f); // Green
//			vertices.push_back(0.0f); // Blue
//		}
//	}
//
//	// Generate vertices for Y-axis (Green)
//	for (int i = 0; i <= segments; ++i) {
//		float y = -length / 2 + (i * segmentLength);
//		vertices.push_back(0.0f); // X
//		vertices.push_back(y); // Y
//		vertices.push_back(0.0f); // Z
//		vertices.push_back(0.0f); // Red
//		vertices.push_back(1.0f); // Green
//		vertices.push_back(0.0f); // Blue
//
//		// Add marker for the segment
//		if (i < segments) {
//			vertices.push_back(0.0f); // X for segment marker
//			vertices.push_back(y + segmentLength / 2); // Y
//			vertices.push_back(0.0f); // Z
//			vertices.push_back(0.0f); // Red
//			vertices.push_back(1.0f); // Green
//			vertices.push_back(0.0f); // Blue
//		}
//	}
//
//	// Generate vertices for Z-axis (Blue)
//	for (int i = 0; i <= segments; ++i) {
//		float z = -length / 2 + (i * segmentLength);
//		vertices.push_back(0.0f); // X
//		vertices.push_back(0.0f); // Y
//		vertices.push_back(z); // Z
//		vertices.push_back(0.0f); // Red
//		vertices.push_back(0.0f); // Green
//		vertices.push_back(1.0f); // Blue
//
//		// Add marker for the segment
//		if (i < segments) {
//			vertices.push_back(0.0f); // X for segment marker
//			vertices.push_back(0.0f); // Y
//			vertices.push_back(z + segmentLength / 2); // Z
//			vertices.push_back(0.0f); // Red
//			vertices.push_back(0.0f); // Green
//			vertices.push_back(1.0f); // Blue
//		}
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
//AxisRenderer::~AxisRenderer() {
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//}
//
//void AxisRenderer::render(Shader& shader, const glm::mat4& transform) const {
//	shader.use();
//	shader.setMat4("transform", transform);
//
//	glBindVertexArray(VAO);
//
//	// Draw X-axis (Red)
//	glDrawArrays(GL_LINES, 0, (10 * 2) + 1); // segments + 1 vertices for X-axis
//
//	// Draw Y-axis (Green)
//	glDrawArrays(GL_LINES, (10 * 2) + 1, (10 * 2) + 1); // segments + 1 vertices for Y-axis
//
//	// Draw Z-axis (Blue)
//	glDrawArrays(GL_LINES, (10 * 4) + 2, (10 * 2) + 1); // segments + 1 vertices for Z-axis
//}
