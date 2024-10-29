// Window.cpp
#include "Window.h"
#include <iostream>
#include <glad/glad.h>

// Global variables for mouse and rotation handling
float rotationX = 0.0f;
float rotationY = 0.0f;
float lastX = 400.0f;
float lastY = 300.0f;
bool firstMouse = true;
bool mouseButtonPressed = false;
float sensitivity = 0.1f;

// Background color variables(RGBA)

float bgColorR = 0.2f;
float bgColorG = 0.3f;
float bgColorB = 0.1f;
float bgColorA = 1.0f;


GLFWwindow* createWindow(int width, int height, const char* title) {
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return nullptr;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (window == nullptr) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	return window;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (mouseButtonPressed) {
		if (firstMouse) {
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		xoffset *= sensitivity;
		yoffset *= sensitivity;

		rotationX += yoffset;
		rotationY += xoffset;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		mouseButtonPressed = (action == GLFW_PRESS);
		if (!mouseButtonPressed) {
			firstMouse = true; // Reset for the next click
		}
	}
}


// Function to set the background color using glm::vec3
void setBackgroundColor(const glm::vec3& color, float alpha) {
	bgColorR = color.r;
	bgColorG = color.g;
	bgColorB = color.b;
	bgColorA = alpha;
	glClearColor(bgColorR, bgColorG, bgColorB, bgColorA);  // Set the OpenGL clear color
}

