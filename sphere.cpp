//#include "sphere.h"
//#include <cmath> // For sin, cos, M_PI
//
//// Define M_PI if it is not defined
//#ifndef M_PI
//#define M_PI 3.14159265358979323846
//#endif
//
//SphereRenderer::SphereRenderer(float r, int segments, int rings)
//	: radius(r), numSegments(segments), numRings(rings) {
//
//	std::vector<GLfloat> vertices;
//
//	for (int i = 0; i <= numRings; ++i) {
//		float theta = i * M_PI / numRings; // From 0 to π
//		float sinTheta = sin(theta);
//		float cosTheta = cos(theta);
//
//		for (int j = 0; j <= numSegments; ++j) {
//			float phi = j * 2.0f * M_PI / numSegments; // From 0 to 2π
//			float x = cos(phi) * sinTheta; // X coordinate
//			float y = cosTheta; // Y coordinate
//			float z = sin(phi) * sinTheta; // Z coordinate
//
//			// Add vertex position
//			vertices.push_back(radius * x); // X
//			vertices.push_back(radius * y); // Y
//			vertices.push_back(radius * z); // Z
//
//			// Add vertex color (optional)
//			vertices.push_back(0.5f); // R
//			vertices.push_back(0.5f); // G
//			vertices.push_back(0.5f); // B
//		}
//	}
//
//	// Generate indices for drawing the sphere with triangle strips
//	std::vector<GLuint> indices;
//	for (int i = 0; i < numRings; ++i) {
//		for (int j = 0; j < numSegments; ++j) {
//			indices.push_back(i * (numSegments + 1) + j);         // First vertex
//			indices.push_back((i + 1) * (numSegments + 1) + j);   // Second vertex
//			indices.push_back((i + 1) * (numSegments + 1) + (j + 1)); // Third vertex
//			indices.push_back(i * (numSegments + 1) + (j + 1));   // Fourth vertex
//		}
//	}
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//
//	// Vertex buffer
//	GLuint VBO_vertices;
//	glGenBuffers(1, &VBO_vertices);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
//
//	// Index buffer
//	GLuint EBO;
//	glGenBuffers(1, &EBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
//
//	// Position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
//	glEnableVertexAttribArray(0);
//	// Color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
//	glEnableVertexAttribArray(1);
//}
//
//SphereRenderer::~SphereRenderer() {
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//}
//
//void SphereRenderer::render(Shader& shader, const glm::mat4& transform) const {
//	shader.use();
//	shader.setMat4("transform", transform);
//
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLE_STRIP, numSegments * numRings * 4, GL_UNSIGNED_INT, 0); // Draw the sphere
//}



#include "sphere.h"
#include <cmath>
#include <vector>

// Define M_PI if it is not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SphereRenderer::SphereRenderer(float radius, int numSegments, int numRings, glm::vec3 color)
	: radius(radius), numSegments(numSegments), numRings(numRings), color(color) {
	std::vector<GLfloat> vertices;

	for (int i = 0; i <= numRings; ++i) {
		float theta = i * M_PI / numRings; // Latitude
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		for (int j = 0; j <= numSegments; ++j) {
			float phi = j * 2 * M_PI / numSegments; // Longitude
			float sinPhi = sin(phi);
			float cosPhi = cos(phi);

			// Calculate the position
			float x = radius * cosPhi * sinTheta;
			float y = radius * cosTheta;
			float z = radius * sinPhi * sinTheta;

			// Add vertex position
			vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);

			// Optional: Add color for shading (RGB)
			//vertices.push_back(1.0f); // R
			//vertices.push_back(0.0f); // G
			//vertices.push_back(0.0f); // B

			vertices.push_back(color.r);
			vertices.push_back(color.g);
			vertices.push_back(color.b);
		}
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

	// Generate indices for the sphere
	std::vector<GLuint> indices;
	for (int i = 0; i < numRings; ++i) {
		for (int j = 0; j < numSegments; ++j) {
			int first = (i * (numSegments + 1)) + j;
			int second = first + numSegments + 1;

			// Two triangles per segment
			indices.push_back(first);
			indices.push_back(second);
			indices.push_back(first + 1);

			indices.push_back(second);
			indices.push_back(second + 1);
			indices.push_back(first + 1);
		}
	}

	// Store the number of indices
	numIndices = indices.size();

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

SphereRenderer::~SphereRenderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void SphereRenderer::render(Shader& shader, const glm::mat4& transform) const {
	shader.use();
	shader.setMat4("transform", transform);

	glBindVertexArray(VAO);

	// Draw the sphere using the index buffer
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
}
