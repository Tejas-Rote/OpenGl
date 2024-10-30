#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "axisRenderer.h"
#include "window.h"
#include "circle.h"
#include "sphere.h"
#include "axisRendererV3.h"
#include "colorUtils.h"
#include "line.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main() {
	GLFWwindow* window = createWindow(SCR_WIDTH, SCR_HEIGHT, "3D Axes");
	if (window == nullptr) return -1;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set the background color using a hex code
	glm::vec3 backgroundColor = hexToRGB("#131313"); // Example hex color
	setBackgroundColor(backgroundColor);


	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);


	// Example of creating an AxisRenderer with colors from hex codes
	glm::vec3 axisColor = hexToRGB("#858585");   // Orange color
	glm::vec3 markerColor = hexToRGB("#ffffff"); // Green color

	Shader axisShader("axis_vertex_shader.glsl", "axis_fragment_shader.glsl"); // Load your shader files
	AxisRendererV3 axisRenderer(axisColor, // Red X-axis
		axisColor, // Green Y-axis
		axisColor, // Blue Z-axis
		markerColor,
		0.005f, // Marker radius
		10);

	// Define the start and end vertices of the line, along with their colors
	glm::vec3 start(0.0f, 0.0f, 0.0f);  // Start position
	glm::vec3 end(0.5f, 0.5f, 0.5f);    // End position
	glm::vec3 startColor(1.0f, 0.0f, 0.0f);  // Red
	glm::vec3 endColor(0.0f, 0.0f, 1.0f);    // Blue

	Shader lineShader("line_vertex_shader.glsl", "line_fragment_shader.glsl");
	LineRenderer line(start, end, startColor, endColor);



	// Create shaders
	Shader circleShader("circle_vertex_shader.glsl", "circle_fragment_shader.glsl");
	CircleRenderer circle(0.35f, 100, glm::vec3(1.0f, 1.0f, 1.0f)); // Radius, segments, color


	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Set up the projection matrix (perspective projection)
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);

		// Compute the view matrix for camera movement
		glm::mat4 view = glm::lookAt(
			glm::vec3(3.0f * sin(glm::radians(rotationY)), 3.0f * sin(glm::radians(rotationX)), 3.0f * cos(glm::radians(rotationY))), // Camera position
			glm::vec3(0.0f, 0.0f, 0.0f), // Looking at the origin
			glm::vec3(0.0f, 1.0f, 0.0f)  // Up vector
		);

		// Render the axes
		axisRenderer.render(axisShader, view, projection);



		// Model matrix for the circle
		glm::mat4 model = glm::mat4(1.0f);  // Identity matrix

		// Use the shader for rendering the circle
		circleShader.use();
		circleShader.setMat4("projection", projection);
		circleShader.setMat4("view", view);
		circleShader.setMat4("model", model);
		circle.render(circleShader, model);  // Pass the model matrix



		// Use the shader for rendering the line
		lineShader.use();
		lineShader.setMat4("projection", projection);
		lineShader.setMat4("view", view);
		// Set model matrix for the line
		glm::mat4 lineModel = glm::mat4(1.0f);  // Identity model matrix for the line
		lineShader.setMat4("model", lineModel);

		// Render the line
		line.render(lineShader, view);  // Ensure render uses the model matrix






		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
