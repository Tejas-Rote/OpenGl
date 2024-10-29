#include "axisRendererV2.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

AxisRendererV2::AxisRendererV2(float markerRadius, int numMarkers, glm::vec3 axisColor, glm::vec3 markerColor)
	: markerRadius(markerRadius), numMarkers(numMarkers), axisColor(axisColor), markerColor(markerColor) {

	// Axis lines (similar to AxisRenderer)
	//GLfloat vertices[] = {
	//	//// X-axis (white)
	//	-1.0f, 0.0f, 0.0f,  0.75f, 0.75f,0.75f,
	//	 1.0f, 0.0f, 0.0f,  0.75f, 0.75f,0.75f,

	//	 // // Y-axis (white)
	//	  0.0f, -1.0f, 0.0f,  0.75f, 0.75f,0.75f,
	//	  0.0f,  1.0f, 0.0f,  0.75f, 0.75f,0.75f,

	//	  // Z-axis (white)
	//	  0.0f, 0.0f, -1.0f,  0.75f, 0.75f,0.75f,
	//	  0.0f, 0.0f,  1.0f,  0.75f, 0.75f,0.75f

	//};

	// Initialize Axis data
	GLfloat vertices[] = {
		// X-axis (red or custom color)
		-1.0f, 0.0f, 0.0f,  axisColor.r, axisColor.g, axisColor.b,
		 1.0f, 0.0f, 0.0f,  axisColor.r, axisColor.g, axisColor.b,

		 // Y-axis (green or custom color)
		  0.0f, -1.0f, 0.0f, axisColor.r, axisColor.g, axisColor.b,
		  0.0f,  1.0f, 0.0f, axisColor.r, axisColor.g, axisColor.b,

		  // Z-axis (blue or custom color)
		   0.0f, 0.0f, -1.0f, axisColor.r, axisColor.g, axisColor.b,
		   0.0f, 0.0f,  1.0f, axisColor.r, axisColor.g, axisColor.b
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);  // Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));  // Color
	glEnableVertexAttribArray(1);

	// Initialize the sphere renderer for unit markers
	sphereRenderer = new SphereRenderer(markerRadius, 36, 18, markerColor);  // 20 segments/20 rings for smooth spheres
}

AxisRendererV2::~AxisRendererV2() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	delete sphereRenderer;
}

void AxisRendererV2::render(Shader& shader, Shader& sphereShader, const glm::mat4& transform) const {
	shader.use();
	shader.setMat4("transform", transform);

	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, 6);  // Draw the 3 axes

	// Render spheres along each axis as unit markers
	sphereShader.use();

	for (int i = 1; i <= numMarkers; ++i) {
		// Calculate the transformation for each sphere
		float markerPos = (float)i / (float)numMarkers;

		// X-axis markers
		glm::mat4 sphereTransform = glm::translate(transform, glm::vec3(markerPos, 0.0f, 0.0f));
		sphereShader.setMat4("transform", sphereTransform);
		sphereRenderer->render(sphereShader, sphereTransform);

		// Y-axis markers
		sphereTransform = glm::translate(transform, glm::vec3(0.0f, markerPos, 0.0f));
		sphereShader.setMat4("transform", sphereTransform);
		sphereRenderer->render(sphereShader, sphereTransform);

		// Z-axis markers
		sphereTransform = glm::translate(transform, glm::vec3(0.0f, 0.0f, markerPos));
		sphereShader.setMat4("transform", sphereTransform);
		sphereRenderer->render(sphereShader, sphereTransform);
	}



	// Negative direction markers
	for (int i = 1; i <= numMarkers; ++i) {
		float markerPos = -(float)i / (float)numMarkers;  // Note the negative sign for the negative side

		// X-axis negative markers
		glm::mat4 sphereTransform = glm::translate(transform, glm::vec3(markerPos, 0.0f, 0.0f));
		sphereShader.setMat4("transform", sphereTransform);
		sphereRenderer->render(sphereShader, sphereTransform);

		// Y-axis negative markers
		sphereTransform = glm::translate(transform, glm::vec3(0.0f, markerPos, 0.0f));
		sphereShader.setMat4("transform", sphereTransform);
		sphereRenderer->render(sphereShader, sphereTransform);

		// Z-axis negative markers
		sphereTransform = glm::translate(transform, glm::vec3(0.0f, 0.0f, markerPos));
		sphereShader.setMat4("transform", sphereTransform);
		sphereRenderer->render(sphereShader, sphereTransform);
	}

}
