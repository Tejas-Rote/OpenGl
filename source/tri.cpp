//#include "tri.h"
//#include "logger.h"  // Logger for logging events
//
//// Vertex shader source code
//const char* vertexSource = R"(
//    #version 330 core
//    layout (location = 0) in vec3 aPos;
//
//    void main() {
//        gl_Position = vec4(aPos, 1.0);
//    }
//)";
//
//// Fragment shader source code
//const char* fragmentSource = R"(
//    #version 330 core
//    out vec4 FragColor;
//
//    void main() {
//        FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
//    }
//)";
//
//Triangle::Triangle() {
//	Logger::Log("Triangle constructor called", LogLevel::INFO);
//}
//
//Triangle::~Triangle() {
//	Logger::Log("Triangle destructor called", LogLevel::INFO);
//}
//
//void Triangle::create() {
//	Logger::Log("Creating triangle", LogLevel::INFO);
//
//	// Triangle vertex data
//	float vertices[] = {
//		 0.0f,  0.5f, 0.0f, // top
//		-0.5f, -0.5f, 0.0f, // left
//		 0.5f, -0.5f, 0.0f  // right
//	};
//
//	// Create VAO and VBO
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	// Vertex attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	// Create and compile shaders
//	shaderProgram = createShaderProgram(vertexSource, fragmentSource);
//}
//
//void Triangle::draw() {
//	//Logger::Log("Drawing triangle", LogLevel::INFO);
//
//	// Use the shader program and draw the triangle
//	glUseProgram(shaderProgram);
//	glBindVertexArray(VAO);
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//}


#include "tri.h"
#include "logger.h"  // Logger for logging events

// Vertex shader source code
const char* vertexSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

// Fragment shader source code
const char* fragmentSource = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
    }
)";

Triangle::Triangle(const std::vector<float>& vertices) : vertices(vertices) {
	Logger::Log("Triangle constructor called", LogLevel::INFO);
}

Triangle::~Triangle() {
	Logger::Log("Triangle destructor called", LogLevel::INFO);
}

void Triangle::create() {
	Logger::Log("Creating triangle", LogLevel::INFO);

	// Create VAO and VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// Vertex attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Create and compile shaders
	shaderProgram = createShaderProgram(vertexSource, fragmentSource);
}

void Triangle::draw() {
	//Logger::Log("Drawing triangle", LogLevel::INFO);

	// Use the shader program and draw the triangle
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
