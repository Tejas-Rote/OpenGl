//#ifndef AXIS_RENDERER_V2_H
//#define AXIS_RENDERER_V2_H
//
//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include "shader.h"
//#include "sphere.h"  // Include sphere renderer for unit markers
//
//class AxisRendererV2 {
//public:
//	GLuint VAO, VBO;
//	int numMarkers;  // Number of markers (small spheres) on each axis
//	float markerRadius;  // Radius of each marker sphere	
//	SphereRenderer* sphereRenderer;  // Sphere renderer for unit markers
//	glm::vec3 axisColor;   // Custom color for the sphere
//	glm::vec3 markerColor;   // Custom color for the sphere
//
//	AxisRendererV2(float markerRadius, int numMarkers, glm::vec3 axisColor = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 markerColor = glm::vec3(1.0f, 1.0f, 1.0f));
//	~AxisRendererV2();
//
//	// Render the axes and unit markers
//	void render(Shader& shader, Shader& sphereShader, const glm::mat4& transform) const;
//};
//
//#endif // AXIS_RENDERER_V2_H


#ifndef AXIS_RENDERER_V2_H
#define AXIS_RENDERER_V2_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "sphere.h"  // Include sphere renderer for unit markers

class AxisRendererV2 {
public:
	GLuint VAO, VBO;            // Vertex Array Object and Vertex Buffer Object for the axis
	int numMarkers;             // Number of markers (small spheres) on each axis
	float markerRadius;         // Radius of each marker sphere
	SphereRenderer* sphereRenderer;  // Sphere renderer for unit markers
	glm::vec3 axisColor;        // Custom color for the axis
	glm::vec3 markerColor;      // Custom color for the marker spheres

	// Constructor with default colors for the axis and markers
	AxisRendererV2(float markerRadius, int numMarkers,
		glm::vec3 axisColor = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3 markerColor = glm::vec3(1.0f, 1.0f, 1.0f));

	// Destructor to clean up resources
	~AxisRendererV2();

	// Render the axes and unit markers
	void render(Shader& shader, Shader& sphereShader,
		const glm::mat4& view, const glm::mat4& projection, const glm::mat4& model) const;
};

#endif // AXIS_RENDERER_V2_H
