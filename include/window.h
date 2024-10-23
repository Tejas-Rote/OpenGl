#ifndef WINDOW_H
#define WINDOW_H

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "logger.h"
#include <functional>

using namespace std;

class Window {
public:
	// Constructor
	Window(int width, int height, const char* title, float red = 0.07f, float green = 0.13f, float blue = 0.17f, float alpha = 1.0f);

	// Destructor
	~Window();

	// Initialize the window
	bool initialize();

	// window color 
	void setClearColor(float red, float green, float blue, float alpha);


	// Set the display function
	void setDisplayFunction(function<void()> func); // Use std::function
	//void setDisplayFunction(void (*displayFunc)());

	// Main loop
	void mainLoop();

	// Get the GLFW window object
	GLFWwindow* getWindow() const;

	void setBackgroundColor(const std::string& hexColor);

private:
	int width;
	int height;
	const char* title;
	GLFWwindow* window;

	float clearColor[4];

	//// Function pointers for rendering and resizing
	function<void()> displayFunc; // std::function for more flexible callbacks
	//void (*displayFunc)();
	//void (*reshapeFunc)(GLFWwindow*, int, int);
};

#endif // WINDOW_H
