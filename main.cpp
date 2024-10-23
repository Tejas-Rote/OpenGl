#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "window.h"
#include "tri.h"
#include "logger.h"
#include "circle.h"

int main() {
	Logger::Log("Application started", LogLevel::INFO);

	// Create the window
	Window window(800, 800, "OpenGL Triangle", 0.1f, 0.1f, 0.1f, 1.0f);
	window.initialize();

	// Define vertices for the triangle
	std::vector<float> triangleVertices = {
		0.2f,  0.7f, 0.0f,  // Top vertex
		-0.7f, -0.9f, 0.0f,  // Bottom left vertex
		0.6f, -0.1f, 0.0f    // Bottom right vertex
	};


	// Create the triangle
	Triangle triangle(triangleVertices);
	triangle.create();



	// create the circle
	Circle circle(0.0f, 0.0f, 0.5f, 100);
	circle.create();

	// Set the display function
	window.setDisplayFunction([&]() {
		triangle.draw();  // Draw the triangle
		//circle.draw();  // Draw the circle
		});

	// Enter the main loop
	window.mainLoop();

	Logger::Log("Application finished", LogLevel::INFO);
	return 0;
}
