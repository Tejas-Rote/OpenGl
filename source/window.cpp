#include "window.h"


// Convert hex color to RGBA values
void hexToRGBA(const std::string& hex, float& r, float& g, float& b, float& a) {
	std::string color = hex[0] == '#' ? hex.substr(1) : hex;

	unsigned int hexValue;
	std::stringstream ss;
	ss << std::hex << color;
	ss >> hexValue;

	if (color.length() == 6) { // RGB format
		a = 1.0f;
		r = ((hexValue >> 16) & 0xFF) / 255.0f;
		g = ((hexValue >> 8) & 0xFF) / 255.0f;
		b = (hexValue & 0xFF) / 255.0f;
	}
	else if (color.length() == 8) { // RGBA format
		r = ((hexValue >> 24) & 0xFF) / 255.0f;
		g = ((hexValue >> 16) & 0xFF) / 255.0f;
		b = ((hexValue >> 8) & 0xFF) / 255.0f;
		a = (hexValue & 0xFF) / 255.0f;
	}
	else {
		std::cerr << "Invalid hex color format!" << std::endl;
	}
}

// Method to change the clear color dynamically using a hex code
void Window::setBackgroundColor(const std::string& hexColor) {
	float r, g, b, a;
	hexToRGBA(hexColor, r, g, b, a);
	setClearColor(r, g, b, a); // Use the existing setClearColor method
}

// Constructor
Window::Window(int width, int height, const char* title, float red, float green, float blue, float alpha)
	: width(width), height(height), title(title), window(nullptr), displayFunc(nullptr) {
	clearColor[0] = red;
	clearColor[1] = green;
	clearColor[2] = blue;
	clearColor[3] = alpha;
}
// Destructor
Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

// Initialize the window
bool Window::initialize() {
	// Initialize GLFW
	if (!glfwInit()) {
		Logger::Log("Failed to initialize GLFW", LogLevel::ERROR);
		return false;
	}

	// version of glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create the window
	window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!window) {
		Logger::Log("Failed to create GLFW window", LogLevel::ERROR);
		glfwTerminate();
		return false;
	}

	// Make OpenGL context current
	glfwMakeContextCurrent(window);
	Logger::Log("Window initialized: " + std::string(title), LogLevel::INFO);

	// Load OpenGL function pointers using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Logger::Log("Failed to initialize GLAD", LogLevel::ERROR);
		return false;
	}

	// Set the viewport
	glViewport(0, 0, width, height);

	return true;
}

// Method to change the clear color dynamically
void Window::setClearColor(float red, float green, float blue, float alpha) {
	clearColor[0] = red;
	clearColor[1] = green;
	clearColor[2] = blue;
	clearColor[3] = alpha;
}


// Set the display function
void Window::setDisplayFunction(std::function<void()> func) {
	displayFunc = func; // Assign the std::function
}


void Window::mainLoop() {
	while (!glfwWindowShouldClose(window)) {
		// Set the clear color and clear the screen
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		// Call the display function if available
		if (displayFunc) {
			displayFunc(); // This will execute your custom rendering logic
		}

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}
}




// Get GLFW window
GLFWwindow* Window::getWindow() const {
	return window;
}


