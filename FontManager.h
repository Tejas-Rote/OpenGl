// FontManager.h
#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <map>
#include <string>
#include <glad/glad.h> 
#include <GLFW/glfw3.h> // Make sure to include this for OpenGL types
#include <glm/glm.hpp>
#include "shader.h" // Include the Shader header for using Shader in renderText

struct Character {
	GLuint textureID;   // ID handle of the glyph texture
	glm::ivec2 size;    // Size of glyph
	glm::ivec2 bearing; // Offset from baseline to left/top of glyph
	GLuint advance;     // Horizontal offset to advance to next glyph
};

class FontManager {
public:
	FontManager();
	~FontManager();

	void loadFont(const std::string& path, unsigned int fontSize);
	void renderText(const std::string& text, float x, float y, float scale, const glm::vec3& color, Shader& shader);

private:
	std::map<char, Character> characters;
	GLuint VAO, VBO;
	FT_Library ft;
};

#endif // FONT_MANAGER_H
