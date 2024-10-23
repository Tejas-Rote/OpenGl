#include <circle.h>
#include<logger.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Circle::Circle(float x, float y, float radius, int segments) : x(x), y(y), radius(radius), segments(segments) {
	Logger::Log("Circle createad", LogLevel::INFO);
}


Circle::~Circle() {
	Logger::Log("Circle destroyed", LogLevel::INFO);
}

void Circle::create() {
	// Generate vertices for the circle
	float* vertices = new float[segments * 2];
	for (int i = 0; i < segments; ++i) {
		float angle = 2.0f * M_PI * i / segments;
		vertices[i * 2] = x + radius * cos(angle); // X coordinate
		vertices[i * 2 + 1] = y + radius * sin(angle); // Y coordinate
	}

	// Create and bind the Vertex Array Object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Create a Vertex Buffer Object and copy the vertices to it
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, segments * 2 * sizeof(float), vertices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Clean up
	delete[] vertices;

	// Compile shaders
	const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 position;
        void main() {
            gl_Position = vec4(position, 0.0, 1.0);
        }
    )";

	const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 fragColor;
        void main() {
            fragColor = vec4(1.0, 0.5, 0.0, 1.0); // Orange color
        }
    )";

	createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void Circle::draw() {
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, segments);
	Logger::Log("Drawing circle at (" + std::to_string(x) + ", " + std::to_string(y) + ") with radius " + std::to_string(radius), LogLevel::INFO);
}