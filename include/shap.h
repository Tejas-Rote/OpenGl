// Shape.h
#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>
#include<logger.h>

class Shape {
public:
	Shape();
	virtual ~Shape();

	virtual void create() = 0;   // Pure virtual function for creating the shape
	virtual void draw() = 0;     // Pure virtual function for rendering the shape

protected:
	unsigned int VAO, VBO;       // Vertex Array Object, Vertex Buffer Object
	unsigned int shaderProgram;  // Shader program

	unsigned int compileShader(const char* source, GLenum type);
	unsigned int createShaderProgram(const char* vertexSource, const char* fragmentSource);
};

#endif // SHAPE_H
