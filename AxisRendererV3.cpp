#include "axisRendererV3.h"
#include <glm/gtc/matrix_transform.hpp>

AxisRendererV3::AxisRendererV3(glm::vec3 colorX, glm::vec3 colorY, glm::vec3 colorZ, glm::vec3 markerColor, float markerRadius, int numMarkers)
	: axisColorX(colorX), axisColorY(colorY), axisColorZ(colorZ), markerColor(markerColor), markerRadius(markerRadius), numMarkers(numMarkers), sphereRenderer(markerRadius, 20, 20, markerColor) {

	GLfloat axisVertices[] = {
		// Positions             // Colors
		-1.0f, 0.0f, 0.0f,      colorX.r, colorX.g, colorX.b, // X-axis start
		 1.0f, 0.0f, 0.0f,      colorX.r, colorX.g, colorX.b, // X-axis end
		 0.0f, -1.0f, 0.0f,     colorY.r, colorY.g, colorY.b, // Y-axis start
		 0.0f,  1.0f, 0.0f,     colorY.r, colorY.g, colorY.b, // Y-axis end
		 0.0f, 0.0f, -1.0f,     colorZ.r, colorZ.g, colorZ.b, // Z-axis start
		 0.0f, 0.0f,  1.0f,     colorZ.r, colorZ.g, colorZ.b  // Z-axis end
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axisVertices), axisVertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

AxisRendererV3::~AxisRendererV3() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void AxisRendererV3::render(Shader& shader, const glm::mat4& view, const glm::mat4& projection) {
	// Render axes
	shader.use();
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	glm::mat4 model = glm::mat4(1.0f); // Identity model matrix
	shader.setMat4("model", model);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6); // Draw 6 vertices for the axes
	glBindVertexArray(0);

	// Render spheres at the ends of each axis
	glm::mat4 sphereModel;
	for (int i = 1; i <= numMarkers; ++i) {
		// X-axis markers
		sphereModel = glm::translate(glm::mat4(1.0f), glm::vec3(i * 0.1f, 0.0f, 0.0f)); // Move along X
		sphereRenderer.render(shader, sphereModel);

		sphereModel = glm::translate(glm::mat4(1.0f), glm::vec3(-i * 0.1f, 0.0f, 0.0f)); // Move along -X
		sphereRenderer.render(shader, sphereModel);

		// Y-axis markers
		sphereModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, i * 0.1f, 0.0f)); // Move along Y
		sphereRenderer.render(shader, sphereModel);

		sphereModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -i * 0.1f, 0.0f)); // Move along -Y
		sphereRenderer.render(shader, sphereModel);

		// Z-axis markers
		sphereModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, i * 0.1f)); // Move along Z
		sphereRenderer.render(shader, sphereModel);

		sphereModel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -i * 0.1f)); // Move along -Z
		sphereRenderer.render(shader, sphereModel);
	}
}
