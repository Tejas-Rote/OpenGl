//#include <iostream>
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "shader.h"
//#include "axisRenderer.h"
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//float rotationX = 0.0f;
//float rotationY = 0.0f;
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//bool mouseButtonPressed = false;
//float sensitivity = 0.1f;
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//	if (mouseButtonPressed) {
//		if (firstMouse) {
//			lastX = xpos;
//			lastY = ypos;
//			firstMouse = false;
//		}
//
//		float xoffset = xpos - lastX;
//		float yoffset = lastY - ypos;
//		lastX = xpos;
//		lastY = ypos;
//
//		xoffset *= sensitivity;
//		yoffset *= sensitivity;
//
//		rotationX += yoffset;
//		rotationY += xoffset;
//	}
//}
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
//	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
//		mouseButtonPressed = true;
//	}
//	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
//		mouseButtonPressed = false;
//		firstMouse = true;
//	}
//}
//
//int main() {
//	if (!glfwInit()) {
//		std::cerr << "Failed to initialize GLFW" << std::endl;
//		return -1;
//	}
//
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Axes", NULL, NULL);
//	if (window == NULL) {
//		std::cerr << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cerr << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetMouseButtonCallback(window, mouse_button_callback);
//
//	Shader shader("axis_vertex_shader.glsl", "axis_fragment_shader.glsl");
//	AxisRenderer axisRenderer;
//
//	while (!glfwWindowShouldClose(window)) {
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		glm::mat4 transform = glm::mat4(1.0f);
//		transform = glm::rotate(transform, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
//		transform = glm::rotate(transform, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
//		axisRenderer.render(shader, transform);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//
//// before freetype addition for text rendering


#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "axisRenderer.h"
#include "window.h"
#include "circle.h"
#include "sphere.h"
#include "axisRendererV2.h"
#include "colorUtils.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

int main() {
	GLFWwindow* window = createWindow(SCR_WIDTH, SCR_HEIGHT, "3D Axes");
	if (window == nullptr) return -1;

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glm::vec3 bgColor = hexToRGB("#2E2E2E");

	// Call setBackgroundColor to set the background color
	//setBackgroundColor(bgColor, 1.0f); // Now it sets the clear color

	// Set the background color using a hex code
	glm::vec3 backgroundColor = hexToRGB("#131313"); // Example hex color
	setBackgroundColor(backgroundColor);


	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);


	// Example of creating an AxisRenderer with colors from hex codes
	glm::vec3 axisColor = hexToRGB("#858585");   // Orange color
	glm::vec3 markerColor = hexToRGB("#ffffff"); // Green color



	Shader axisShader("axis_vertex_shader.glsl", "axis_fragment_shader.glsl");
	//AxisRenderer axisRenderer;
	AxisRendererV2 axisRendererV2(0.005f, 10, axisColor, markerColor);  // Unit markers: 10 markers per axis, 0.05 radius



	Shader circleShader("circle_vertex_shader.glsl", "circle_fragment_shader.glsl");
	//CircleRenderer circleRenderer(0.005f, 200, glm::vec3(1.0f, 1.0f, 1.0f)); // Radius 0.5, 100 segments



	Shader sphereShader("sphere_vertex_shader.glsl", "sphere_fragment_shader.glsl"); // Load sphere shaders
	//SphereRenderer sphereRenderer(0.005f, 50, 50); // radius, numSegments, numRings





	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// creating transform for camerea movement
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::rotate(transform, glm::radians(rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
		transform = glm::rotate(transform, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));



		// axis rendering
		//axisRenderer.render(shader, transform);
		axisRendererV2.render(axisShader, sphereShader, transform);



		// Circle rendering
		//circleRenderer.render(circleShader, transform);



		//sphere rendering
		//sphereRenderer.render(sphereShader, transform);




		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}




























//WITH TEXT RENDERING

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <iostream>
//#include <map>
//#include <string>
//
//// Shader sources (inlined for simplicity)
//const char* vertexShaderSource = R"(
//#version 330 core
//layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
//out vec2 TexCoords;
//uniform mat4 projection;
//void main() {
//    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
//    TexCoords = vertex.zw;
//}
//)";
//
//const char* fragmentShaderSource = R"(
//#version 330 core
//in vec2 TexCoords;
//out vec4 color;
//uniform sampler2D text;
//uniform vec3 textColor;
//void main() {
//    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
//    color = vec4(textColor, 1.0) * sampled;
//}
//)";
//
//// Struct to hold character information
//struct Character {
//	GLuint TextureID;   // ID handle of the glyph texture
//	glm::ivec2 Size;    // Size of glyph
//	glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
//	GLuint Advance;     // Horizontal offset to advance to next glyph
//};
//
//// Global variables
//std::map<GLchar, Character> Characters;
//GLuint VAO, VBO;
//
//// Function prototypes
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void processInput(GLFWwindow* window);
//void RenderText(GLuint shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
//GLuint compileShader(const char* source, GLenum type);
//GLuint createShaderProgram();
//void checkOpenGLError(const std::string& location);
//
//int main() {
//	// Initialize GLFW
//	if (!glfwInit()) {
//		std::cerr << "ERROR::GLFW::Failed to initialize GLFW" << std::endl;
//		return -1;
//	}
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// Create window
//	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Text Rendering", NULL, NULL);
//	if (window == NULL) {
//		std::cerr << "ERROR::GLFW::Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//	// Initialize GLAD
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cerr << "ERROR::GLAD::Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// Compile and link shaders
//	GLuint shaderProgram = createShaderProgram();
//	if (!shaderProgram) {
//		std::cerr << "ERROR::SHADER::Failed to create shader program" << std::endl;
//		return -1;
//	}
//	glUseProgram(shaderProgram);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//
//	// Set up FreeType
//	FT_Library ft;
//	if (FT_Init_FreeType(&ft)) {
//		std::cerr << "ERROR::FREETYPE::Could not init FreeType Library" << std::endl;
//		return -1;
//	}
//
//	// Load a font
//	FT_Face face;
//	if (FT_New_Face(ft, "SpaceMono-regular.ttf", 0, &face)) {
//		std::cerr << "ERROR::FREETYPE::Failed to load font" << std::endl;
//		return -1;
//	}
//	FT_Set_Pixel_Sizes(face, 0, 48); // Set font size to 48
//	std::cout << "FREETYPE::Font loaded successfully" << std::endl;
//
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction
//
//	// Load first 128 characters of ASCII set
//	for (GLubyte c = 0; c < 128; c++) {
//		// Load character glyph
//		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
//			std::cerr << "ERROR::FREETYPE::Failed to load Glyph " << (char)c << std::endl;
//			continue;
//		}
//
//		// Generate texture
//		GLuint texture;
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexImage2D(
//			GL_TEXTURE_2D,
//			0,
//			GL_RED,
//			face->glyph->bitmap.width,
//			face->glyph->bitmap.rows,
//			0,
//			GL_RED,
//			GL_UNSIGNED_BYTE,
//			face->glyph->bitmap.buffer
//		);
//		checkOpenGLError("Generating Texture");
//
//		// Set texture options
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		// Store character for later use
//		Character character = {
//			texture,
//			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//			static_cast<GLuint>(face->glyph->advance.x)
//		};
//		Characters.insert(std::pair<GLchar, Character>(c, character));
//	}
//	FT_Done_Face(face);
//	FT_Done_FreeType(ft);
//
//	// Configure VAO/VBO for texture quads
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//	checkOpenGLError("VAO/VBO Setup");
//
//	// Set up the projection matrix for 2D rendering
//	glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
//	glUseProgram(shaderProgram);
//	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
//	checkOpenGLError("Setting Projection Matrix");
//
//	// Render loop
//	while (!glfwWindowShouldClose(window)) {
//		processInput(window);
//
//		// Render background
//		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT);
//
//		// Render text
//		RenderText(shaderProgram, "Hello OpenGL", 25.0f, 550.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteProgram(shaderProgram);
//
//	glfwTerminate();
//	return 0;
//}
//
//void RenderText(GLuint shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color) {
//	glUseProgram(shader);
//	glUniform3f(glGetUniformLocation(shader, "textColor"), color.x, color.y, color.z);
//	glActiveTexture(GL_TEXTURE0);
//	glBindVertexArray(VAO);
//
//	std::string::const_iterator c;
//	for (c = text.begin(); c != text.end(); c++) {
//		Character ch = Characters[*c];
//
//		GLfloat xpos = x + ch.Bearing.x * scale;
//		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
//
//		GLfloat w = ch.Size.x * scale;
//		GLfloat h = ch.Size.y * scale;
//		// Update VBO for each character
//		GLfloat vertices[6][4] = {
//			{ xpos,     ypos + h,   0.0f, 0.0f },
//			{ xpos,     ypos,       0.0f, 1.0f },
//			{ xpos + w, ypos,       1.0f, 1.0f },
//
//			{ xpos,     ypos + h,   0.0f, 0.0f },
//			{ xpos + w, ypos,       1.0f, 1.0f },
//			{ xpos + w, ypos + h,   1.0f, 0.0f }
//		};
//		// Render glyph texture over quad
//		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//		checkOpenGLError("Binding Texture");
//		// Update content of VBO memory
//		glBindBuffer(GL_ARRAY_BUFFER, VBO);
//		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		// Render quad
//		glDrawArrays(GL_TRIANGLES, 0, 6);
//		checkOpenGLError("Rendering Glyph");
//		// Advance cursors for next glyph
//		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
//	}
//	glBindVertexArray(0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//}
//
//// Function to compile a shader
//GLuint compileShader(const char* source, GLenum type) {
//	GLuint shader = glCreateShader(type);
//	glShaderSource(shader, 1, &source, NULL);
//	glCompileShader(shader);
//	GLint success;
//	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		char infoLog[512];
//		glGetShaderInfoLog(shader, 512, NULL, infoLog);
//		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
//	}
//	return shader;
//}
//
//// Function to create a shader program
//GLuint createShaderProgram() {
//	GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
//	GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
//
//	GLuint shaderProgram = glCreateProgram();
//	glAttachShader(shaderProgram, vertexShader);
//	glAttachShader(shaderProgram, fragmentShader);
//	glLinkProgram(shaderProgram);
//
//	GLint success;
//	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//	if (!success) {
//		char infoLog[512];
//		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//		std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//	}
//
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragmentShader);
//
//	return shaderProgram;
//}
//
//// Process input
//void processInput(GLFWwindow* window) {
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//}
//
//// Callback for window resizing
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//// Helper function to check for OpenGL errors
//void checkOpenGLError(const std::string& location) {
//	GLenum error;
//	while ((error = glGetError()) != GL_NO_ERROR) {
//		std::cerr << "OpenGL Error at " << location << ": " << error << std::endl;
//	}
//}
