#include "line.h"

// Constructor to initialize line with start and end vertices, and their respective colors
LineRenderer::LineRenderer(const glm::vec3& start, const glm::vec3& end, const glm::vec3& startColor, const glm::vec3& endColor) {
	// Prepare the vertex data (position + color)
	GLfloat tempVertices[] = {
		// Position (x, y, z)    // Color (r, g, b)
		start.x, start.y, start.z, startColor.r, startColor.g, startColor.b,  // First vertex (start)
		end.x,   end.y,   end.z,   endColor.r,   endColor.g,   endColor.b     // Second vertex (end)
	};

	// Copy the tempVertices to the member variable
	for (int i = 0; i < 12; ++i) {
		vertices[i] = tempVertices[i];
	}

	// Generate VAO and VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	// Bind VBO and upload the vertex data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Define position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	// Define color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);  // Unbind VAO
}

// Destructor to clean up the resources
LineRenderer::~LineRenderer() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

// Render function that takes a shader and transformation matrixz
void LineRenderer::render(Shader& shader, const glm::mat4& transform) const {
	shader.use();
	shader.setMat4("transform", transform);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 2);  // Render as a line with 2 vertices
	glBindVertexArray(0);
}
