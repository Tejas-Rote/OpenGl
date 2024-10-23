
#ifndef TRIANGLE_H
#define TRIANGLE_H
#include<vector>

#include <glad/glad.h>
#include "shap.h"

class Triangle : public Shape {
public:
	Triangle(const std::vector<float>& vertices);
	~Triangle();

	void create() override; // Create the VAO, VBO, and shaders for the triangle
	void draw() override;   // Render the triangle
private:
	std::vector<float> vertices; // Vertex data for the triangle

	const char* vertexSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

	const char* fragmentSource = R"(
        #version 330 core
        out vec4 FragColor;

        void main() {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0); // Orange color
        }
    )";
};


#endif // TRIANGLE_H
