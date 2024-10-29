// Window.h
#ifndef WINDOW_H
#define WINDOW_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "colorUtils.h"

// Global variables for mouse and rotation handling
extern float rotationX;
extern float rotationY;
extern float lastX;
extern float lastY;
extern bool firstMouse;
extern bool mouseButtonPressed;
extern float sensitivity;
// Declare global variables for background color (optional, or could move into a class)
extern float bgColorR;
extern float bgColorG;
extern float bgColorB;
extern float bgColorA;
GLFWwindow* createWindow(int width, int height, const char* title);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void setBackgroundColor(const glm::vec3& color, float alpha = 1.0f); // Declare without GLFWwindow* parameter


#endif // WINDOW_H
